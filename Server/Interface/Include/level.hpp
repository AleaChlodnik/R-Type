/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** level
*/

#pragma once

#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <cmath>
#include <game_struct.h>

#include <i_level.hpp>

namespace r_type {
namespace net {
template <typename T> class AServer;
}
template <typename T> class Level : virtual public ILevel<T> {
  public:
    Level() = default;
    ~Level() = default;

    /**
     * @brief Updates the game state by processing entity movements, handling collisions, and
     * sending messages to clients.
     *
     * This function performs several tasks to update the game state:
     * - Moves entities based on the elapsed time.
     * - Handles collisions between entities.
     * - Sends messages to clients about destroyed entities.
     * - Updates animations and firing mechanisms.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the ComponentManager handling game components.
     * @param entityManager Reference to the EntityManager handling game entities.
     * @param newClock The current time point used to calculate elapsed time.
     * @param bUpdateEntities Pointer to a boolean flag indicating whether entities should be
     * updated.
     */
    void Update(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock,
        bool *bUpdateEntities) override
    {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(newClock - server->GetClock())
                   .count() > 100) {
            *bUpdateEntities = true;

            MoveUpdate(server, componentManager, entityManager, newClock);
            CollisionUpdate(server, componentManager, entityManager, newClock);
            AnimationUpdate(server, componentManager, entityManager, newClock);
            FireUpdate(server, componentManager, entityManager, newClock);
            LevelOne(server, componentManager, entityManager, newClock);
            server->SetClock(server->GetClock() + std::chrono::milliseconds(500));
        }
    }

    /**
     * @brief Initializes and sets up various systems for the level.
     *
     * This function overrides a base class method to initialize and set up the
     * MoveSystem, CollisionSystem, AnimationSystem, and AutoFireSystem using the
     * provided ComponentManager and EntityManager.
     *
     * @param componentManager Reference to the ComponentManager used to manage components.
     * @param entityManager Reference to the EntityManager used to manage entities.
     */
    void SetSystem(ComponentManager &componentManager, EntityManager &entityManager) override
    {
        _moveSystem = std::make_shared<MoveSystem>(componentManager, entityManager);
        _collisionSystem = std::make_shared<CollisionSystem>(componentManager, entityManager);
        _animationSystem = std::make_shared<AnimationSystem>(componentManager, entityManager);
        _autoFireSystem = std::make_shared<AutoFireSystem>(componentManager, entityManager);
    }

    /**
     * @brief Updates the positions of entities and notifies clients of any changes.
     *
     * This function performs the following steps:
     * 1. Retrieves the current positions of entities and stores them.
     * 2. Moves the entities using the move system.
     * 3. Compares the new positions with the previous positions.
     * 4. If an entity's position has changed, sends an update message to all clients.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the ComponentManager.
     * @param entityManager Reference to the EntityManager.
     * @param newClock The current time point.
     */
    void MoveUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        if (auto positionsBefore = componentManager.getComponentMap<PositionComponent>()) {
            std::unordered_map<int, PositionComponent> previousPositions;
            // Save previous positions
            for (auto &pair : **positionsBefore) {
                int entityId = pair.first;
                auto positionComponent = pair.second;
                auto position = std::any_cast<PositionComponent>(&positionComponent);
                if (position) {
                    previousPositions.insert({entityId, *position});
                }
            }
            // Move entities
            _moveSystem.get()->moveEntities(componentManager, entityManager);
            // Compare new positions
            if (auto positionsAfter = componentManager.getComponentMap<PositionComponent>()) {
                for (auto &pair : **positionsAfter) {
                    int entityId = pair.first;
                    auto &newPositionComponent = pair.second;
                    if (auto newPosition =
                            std::any_cast<PositionComponent>(&newPositionComponent)) {
                        auto it = previousPositions.find(entityId);
                        if (it != previousPositions.end()) {
                            auto &oldPosition = it->second;
                            if (oldPosition.x != newPosition->x ||
                                oldPosition.y != newPosition->y) {
                                if (auto spriteData =
                                        componentManager.getComponent<SpriteDataComponent>(
                                            entityId)) {
                                    r_type::net::Message<TypeMessage> msg;
                                    vf2d newPos(newPosition->x, newPosition->y);
                                    msg.header.id = TypeMessage::MoveEntityMessage;
                                    msg << entityId << newPos;
                                    server->MessageAllClients(msg);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Updates the collision status of entities in the game.
     *
     * This function checks for collisions between entities and handles the consequences
     * of those collisions, such as updating health, removing entities, and adding new entities.
     * It also handles entities that go off-screen.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the component manager.
     * @param entityManager Reference to the entity manager.
     * @param newClock The current time point for the update.
     */
    void CollisionUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        std::vector<int> entitiesToRemove;
        std::vector<int> entitiesToAdd;
        auto beforeCollisionEntities = entityManager.getAllEntities();

        for (size_t i = 0; i < beforeCollisionEntities.size(); ++i) {
            int entityId1 = beforeCollisionEntities[i].getId();
            for (size_t j = i + 1; j < beforeCollisionEntities.size(); ++j) {
                int entityId2 = beforeCollisionEntities[j].getId();
                // Check for collision
                if (_collisionSystem.get()->checkCollision(
                        componentManager, entityId1, entityId2)) {
                    // component of entity 1
                    auto player1 = componentManager.getComponent<PlayerComponent>(entityId1);
                    auto shooterEnemy1 = componentManager.getComponent<ShootComponent>(entityId1);
                    auto playerMissile1 =
                        componentManager.getComponent<PlayerMissileComponent>(entityId1);
                    auto enemyMissile1 =
                        componentManager.getComponent<EnemyMissileComponent>(entityId1);
                    auto playerHealth1 = componentManager.getComponent<HealthComponent>(entityId1);
                    auto basicMonster1 =
                        componentManager.getComponent<BasicMonsterComponent>(entityId1);
                    auto powerUp1 = componentManager.getComponent<PowerUpComponent>(entityId1);

                    // component of entity 2
                    auto shooterEnemy2 = componentManager.getComponent<ShootComponent>(entityId2);
                    auto enemyMissile2 =
                        componentManager.getComponent<EnemyMissileComponent>(entityId2);
                    auto basicMonster2 =
                        componentManager.getComponent<BasicMonsterComponent>(entityId2);
                    auto player2 = componentManager.getComponent<PlayerComponent>(entityId2);
                    auto playerHealth2 = componentManager.getComponent<HealthComponent>(entityId2);
                    auto playerMissile2 =
                        componentManager.getComponent<PlayerMissileComponent>(entityId2);
                    auto powerUp2 = componentManager.getComponent<PowerUpComponent>(entityId2);

                    // Handle collision
                    if (player1) {
                        if (playerHealth1) {
                            if (shooterEnemy2 || enemyMissile2) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                                playerHealth1.value()->health -= 1;
                            }
                            if (basicMonster2) {
                                playerHealth1.value()->health -= 1;
                            }
                            if (playerHealth1.value()->health <= 0) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId1) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId1);
                                }
                            }
                            r_type::net::Message<TypeMessage> updLivesMsg;
                            updLivesMsg.header.id = TypeMessage::UpdateInfoBar;
                            updLivesMsg << server->UpdateInfoBar(entityId1);
                            server->MessageClient(server->getClientById(server->_deqConnections,
                                                      server->GetPlayerClientId(entityId1)),
                                updLivesMsg);
                        }
                        // when player collides with power up
                        if (powerUp2) {
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId2) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId2);
                            }
                            Entity weapon = server->GetEntityFactory().createForceWeapon(
                                entityManager, componentManager, entityId1);
                            entitiesToAdd.push_back(weapon.getId());
                        }
                    } else if (playerMissile1) {
                        if (shooterEnemy2 || enemyMissile2 || basicMonster2) {
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId1) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId1);
                            }
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId2) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId2);
                            }
                        }
                    } else if (player2) {
                        if (playerHealth2) {
                            if (shooterEnemy1 || enemyMissile1) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId1) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId1);
                                }
                                playerHealth2.value()->health -= 1;
                            }
                            if (basicMonster1) {
                                playerHealth2.value()->health -= 1;
                            }
                            if (playerHealth2.value()->health <= 0) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                            }
                            r_type::net::Message<TypeMessage> updLivesMsg;
                            updLivesMsg.header.id = TypeMessage::UpdateInfoBar;
                            updLivesMsg << server->UpdateInfoBar(entityId2);
                            server->MessageClient(server->getClientById(server->_deqConnections,
                                                      server->GetPlayerClientId(entityId2)),
                                updLivesMsg);
                        }
                        // when player collides with power up
                        if (powerUp1) {
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId1) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId1);
                            }
                            Entity weapon = server->GetEntityFactory().createForceWeapon(
                                entityManager, componentManager, entityId2);
                            entitiesToAdd.push_back(weapon.getId());
                        }
                    } else if (playerMissile2) {
                        if (shooterEnemy1 || enemyMissile1 || basicMonster1) {
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId1) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId1);
                            }
                            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                    entityId2) == entitiesToRemove.end()) {
                                entitiesToRemove.push_back(entityId2);
                            }
                        }
                    }
                }
            }
        }

        // Add entities
        for (int entityId : entitiesToAdd) {
            r_type::net::Message<TypeMessage> msg;
            msg.header.id = TypeMessage::CreateEntityMessage;
            msg << server->InitiateWeaponForce(entityId);
            server->MessageAllClients(msg);
        }
        // Remove entities
        for (int entityId : entitiesToRemove) {
            r_type::net::Message<TypeMessage> msg;
            msg.header.id = TypeMessage::DestroyEntityMessage;
            msg << entityId;
            server->MessageAllClients(msg);
            componentManager.removeEntityFromAllComponents(entityId);
            entityManager.removeEntity(entityId);
        }
        // Remove entities when they go off-screen
        auto afterCollisionEntities = entityManager.getAllEntities();
        for (const auto &entity : afterCollisionEntities) {
            int entityId = entity.getId();
            if (_collisionSystem.get()->checkOffScreen(componentManager, entityId)) {
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::DestroyEntityMessage;
                msg << entityId;
                server->MessageAllClients(msg);
                componentManager.removeEntityFromAllComponents(entityId);
                entityManager.removeEntity(entityId);
            }
        }
    }

    /**
     * @brief Updates the animations of entities and sends messages to clients if animations have
     * changed.
     *
     * This function performs the following steps:
     * 1. Retrieves the current animation components from the component manager.
     * 2. Saves the current state of animations.
     * 3. Updates the animations using the animation system.
     * 4. Compares the new state of animations with the previous state.
     * 5. Sends messages to all clients if any animations have changed.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the component manager.
     * @param entityManager Reference to the entity manager.
     * @param newClock The current time point.
     */
    void AnimationUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        if (auto animationsBefore = componentManager.getComponentMap<AnimationComponent>()) {

            std::unordered_map<int, AnimationComponent> previousAnimations;

            // Save previous animations
            for (const auto &pair : **animationsBefore) {
                int entityId = pair.first;
                const auto animationComponent = pair.second;
                auto animation = std::any_cast<AnimationComponent>(&animationComponent);
                if (animation) {
                    previousAnimations.insert({entityId, *animation});
                }
            }
            _animationSystem->AnimationEntities(componentManager, entityManager, 0.2);
            // Compare new Animations
            if (auto animationsAfter = componentManager.getComponentMap<AnimationComponent>()) {
                for (const auto &pair : **animationsAfter) {
                    int entityId = pair.first;
                    const auto &newAnimationComponent = pair.second;
                    auto newAnimation = std::any_cast<AnimationComponent>(&newAnimationComponent);
                    if (newAnimation) {
                        auto it = previousAnimations.find(entityId);
                        if (it != previousAnimations.end()) {
                            const auto &oldAnimation = it->second;
                            if (oldAnimation != *newAnimation) {
                                r_type::net::Message<TypeMessage> msg;
                                msg.header.id = TypeMessage::AnimateEntityMessage;
                                msg << entityId << newAnimation->dimension << newAnimation->offset;
                                server->MessageAllClients(msg);
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Updates the firing mechanism of entities in the game.
     *
     * This function handles the automatic firing system and processes the firing logic for
     * entities. It retrieves all entities and checks if they can shoot. If an entity can shoot, it
     * sends a message to all clients to create an enemy missile and sets the entity's canShoot
     * flag to false.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the ComponentManager handling components.
     * @param entityManager Reference to the EntityManager handling entities.
     * @param newClock The current time point used for timing events.
     */
    void FireUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        // auto fire system
        _autoFireSystem->handleAutoFire(componentManager, entityManager);
        auto shootComponentMap = componentManager.getComponentMap<ShootComponent>();
        if (shootComponentMap) {
            for (auto &pair : **shootComponentMap) {
                int entityId = pair.first;
                auto &shootComponent = pair.second;
                if (auto shootInfo = std::any_cast<ShootComponent>(&shootComponent)) {
                    if (shootInfo->canShoot) {
                        auto weapon = componentManager.getComponent<WeaponComponent>(entityId);
                        if (weapon) {
                            Entity missile = server->GetEntityFactory().createPlayerMissile(
                                entityManager, componentManager, entityId);
                            r_type::net::Message<TypeMessage> weaponMissileMsg;
                            weaponMissileMsg.header.id = TypeMessage::CreateEntityMessage;
                            weaponMissileMsg << server->InitiatePlayerMissile(missile.getId());
                            server->MessageAllClients(weaponMissileMsg);
                            shootInfo->canShoot = false;
                        } else {
                            r_type::net::Message<TypeMessage> enemyMissileMsg;
                            enemyMissileMsg.header.id = TypeMessage::CreateEntityMessage;
                            enemyMissileMsg << server->InitiateEnemyMissile(entityId);
                            server->MessageAllClients(enemyMissileMsg);
                            shootInfo->canShoot = false;
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Handles the spawning of entities for Level One.
     *
     * This function is responsible for spawning basic monsters and shooter enemies
     * at specific intervals defined by the game parameters. It checks the elapsed
     * time since the last spawn of each entity type and spawns new entities if the
     * required time has passed.
     *
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param newClock The current time point used for timing calculations.
     */
    void LevelOne(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(
                server->GetClock() - _basicMonsterSpawnTime)
                .count() > _gameParameters.spawnTimeBasicMonster) {
            SpawnEntity(server, entityManager, componentManager, _gameParameters.nbrOfBasicMonster,
                EntityFactory::EnemyType::BasicMonster);
            _basicMonsterSpawnTime = server->GetClock();
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(
                server->GetClock() - _shooterEnemySpawnTime)
                .count() > _gameParameters.spawnTimeShooterEnemy) {
            SpawnEntity(server, entityManager, componentManager, _gameParameters.nbrOfShooterEnemy,
                EntityFactory::EnemyType::ShooterEnemy);
            _shooterEnemySpawnTime = server->GetClock();
        }
    }

    /**
     * @brief Spawns a specified number of enemy entities in the game.
     *
     * This function creates and spawns a specified number of enemy entities of a given type
     * at random positions within the game world. The enemy entities are then broadcasted to
     * all connected clients.
     *
     * @tparam T The type of the server.
     * @param server A pointer to the server instance.
     * @param entityManager Reference to the EntityManager responsible for managing entities.
     * @param componentManager Reference to the ComponentManager responsible for managing
     * components.
     * @param nbrOfEnemy The number of enemy entities to spawn.
     * @param enemyType The type of enemy to spawn (e.g., BasicMonster, ShooterEnemy).
     */
    void SpawnEntity(r_type::net::AServer<T> *server, EntityManager &entityManager,
        ComponentManager &componentManager, int nbrOfEnemy, EntityFactory::EnemyType enemyType)
    {
        switch (enemyType) {
        case EntityFactory::EnemyType::BasicMonster: {
            int posX, posY;
            int i = 0;
            posY = static_cast<int>((rand() % 70) + 10);
            posX = 100;
            while (i < nbrOfEnemy) {
                Entity Monster = server->GetEntityFactory().createBasicMonster(
                    entityManager, componentManager, posX, posY);
                posY += (static_cast<int>(rand() % 10) - static_cast<int>(rand() % 10));
                if (posY > 90)
                    posY = static_cast<int>((rand() % 70) + 10);
                posX += 5;
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::CreateEntityMessage;
                msg << server->FormatEntityInformation(Monster.getId());
                server->MessageAllClients(msg);
                i++;
            }
        } break;
        case EntityFactory::EnemyType::ShooterEnemy: {
            int posX, posY;
            int i = 0;
            posX = 99;
            posY = static_cast<int>((rand() % 70) + 10);
            while (i < nbrOfEnemy) {
                Entity ShooterEnemy = server->GetEntityFactory().createShooterEnemy(
                    entityManager, componentManager, posX, posY);
                posX += 5;
                posY += (static_cast<int>(rand() % 20) - static_cast<int>(rand() % 10));

                if (posY > 90)
                    posY = static_cast<int>((rand() % 70) + 10);
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::CreateEntityMessage;
                msg << server->FormatEntityInformation(ShooterEnemy.getId());
                server->MessageAllClients(msg);
                i++;
            }
        } break;
        default:
            break;
        }
    }

    /**
     * @brief Sets the game difficulty based on the provided game parameters.
     *
     * This function sets the game difficulty based on the provided game parameters.
     *
     * @param gameParameters The game parameters to set the difficulty.
     */
    void SetGameParameters(GameParameters gameParameters) { _gameParameters = gameParameters; }

  protected:
    std::shared_ptr<MoveSystem> _moveSystem;
    std::shared_ptr<CollisionSystem> _collisionSystem;
    std::shared_ptr<AnimationSystem> _animationSystem;
    std::shared_ptr<AutoFireSystem> _autoFireSystem;

    std::chrono::system_clock::time_point _basicMonsterSpawnTime =
        std::chrono::system_clock::now();
    std::chrono::system_clock::time_point _shooterEnemySpawnTime =
        std::chrono::system_clock::now();
    std::chrono::system_clock::time_point _spawnTimeMonsterThree;

    GameParameters _gameParameters;
};
} // namespace r_type