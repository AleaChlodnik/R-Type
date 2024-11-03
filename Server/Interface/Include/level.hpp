/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** level
*/

#pragma once

#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <animation_system.hpp>
#include <cmath>
#include <game_struct.hpp>

#include <i_level.hpp>

namespace r_type {
namespace net {
template <typename T> class AServer;
}
/**
 * @brief The Level class template manages the game level, including updating game state,
 * handling collisions, and managing entities.
 *
 * This class template provides methods to update the game state, handle collisions,
 * manage animations, and control the firing mechanisms of entities. It also includes
 * functionality to spawn entities and set game parameters.
 *
 * @tparam T The type of the server.
 */
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
            if (server->_endOfLevel == false) {
                switch (_gameParameters.levelType) {
                case GameState::LevelOne:
                    LevelOne(server, componentManager, entityManager, newClock);
                    break;
                case GameState::LevelTwo:
                    LevelTwo(server, componentManager, entityManager, newClock);
                    break;
                case GameState::LevelThree:
                    LevelThree(server, componentManager, entityManager, newClock);
                    break;
                default:
                    break;
                }
            } else {
                // if (server->_bossActive == false) {
                //     SpawnEntity(server, entityManager, componentManager, 0,
                //         EntityFactory::EnemyType::Boss);
                // }
            }
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
     * @brief Handles the collision action between two entities in the game.
     *
     * This function determines the type of collision between two entities and performs the
     * appropriate actions based on the components of the entities involved. It updates the
     * health, score, and other relevant components, and manages the addition and removal of
     * entities from the game.
     *
     * @tparam T The type of the server.
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the ComponentManager.
     * @param entityManager Reference to the EntityManager.
     * @param entitiesToRemove Vector of entity IDs to be removed from the game.
     * @param entitiesToAdd Vector of entity IDs to be added to the game.
     * @param entityId1 The ID of the first entity involved in the collision.
     * @param entityId2 The ID of the second entity involved in the collision.
     * @return True if a collision was handled, false otherwise.
     */
    static bool collisionAction(r_type::net::AServer<T> *server,
        ComponentManager &componentManager, EntityManager &entityManager,
        std::vector<int> &entitiesToRemove, std::vector<int> &entitiesToAdd, uint32_t entityId1,
        uint32_t entityId2)
    {
        // component of entity 1
        auto player1 = componentManager.getComponent<PlayerComponent>(entityId1);
        auto playerMissile1 = componentManager.getComponent<PlayerMissileComponent>(entityId1);
        auto enemyMissile1 = componentManager.getComponent<EnemyMissileComponent>(entityId1);
        auto playerHealth1 = componentManager.getComponent<HealthComponent>(entityId1);
        auto powerUp1 = componentManager.getComponent<PowerUpComponent>(entityId1);
        auto enemy1 = componentManager.getComponent<EnemyComponent>(entityId1);
        auto forceWeapon1 = componentManager.getComponent<ForceWeaponComponent>(entityId1);
        auto forceMissile1 = componentManager.getComponent<ForceMissileComponent>(entityId1);

        // component of entity 2
        auto enemyMissile2 = componentManager.getComponent<EnemyMissileComponent>(entityId2);
        auto player2 = componentManager.getComponent<PlayerComponent>(entityId2);
        auto playerHealth2 = componentManager.getComponent<HealthComponent>(entityId2);
        auto playerMissile2 = componentManager.getComponent<PlayerMissileComponent>(entityId2);
        auto powerUp2 = componentManager.getComponent<PowerUpComponent>(entityId2);
        auto enemy2 = componentManager.getComponent<EnemyComponent>(entityId2);
        auto forceWeapon2 = componentManager.getComponent<ForceWeaponComponent>(entityId2);
        auto forceMissile2 = componentManager.getComponent<ForceMissileComponent>(entityId2);

        // Handle collision
        if (player1) {
            if (playerHealth1) {
                if (enemy2 || enemyMissile2) {
                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                        entitiesToRemove.end()) {
                        entitiesToRemove.push_back(entityId2);
                        playerHealth1.value()->lives -= 1;
                    }
                }
                r_type::net::Message<TypeMessage> updLivesMsg;
                updLivesMsg.header.id = TypeMessage::UpdateInfoBar;
                updLivesMsg << server->UpdateInfoBar(entityId1);
                server->MessageClient(server->getClientById(server->_deqConnections,
                                          server->GetPlayerClientId(entityId1)),
                    updLivesMsg);
                if (playerHealth1.value()->lives <= 0) {
                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                        entitiesToRemove.end()) {
                        entitiesToRemove.push_back(entityId1);
                    }
                }
            }
            // when player collides with power up
            if (powerUp2) {
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                    entitiesToRemove.end()) {
                    entitiesToRemove.push_back(entityId2);
                }
                auto linkForceComponent =
                    componentManager.getComponent<LinkForceComponent>(entityId1);
                if (linkForceComponent.value()->targetId != -1) {
                    auto forceWeapon = componentManager.getComponent<ForceWeaponComponent>(
                        linkForceComponent.value()->targetId);
                    if (forceWeapon) {
                        if (forceWeapon.value()->level < 3) {
                            forceWeapon.value()->level += 1;
                        }
                    }
                } else {
                    Entity weapon = server->GetEntityFactory().createForceWeapon(
                        entityManager, componentManager, entityId1);
                    entitiesToAdd.push_back(weapon.getId());
                    auto linkForceComponent =
                        componentManager.getComponent<LinkForceComponent>(entityId1);
                    linkForceComponent.value()->targetId = weapon.getId();
                }
            }
            if (forceWeapon2) {
                auto frontComponent = componentManager.getComponent<FrontComponent>(entityId1);
                if (frontComponent) {
                    frontComponent.value()->targetId = entityId2;
                    auto forceWeapon = componentManager.getComponent<ForceWeaponComponent>(
                        frontComponent.value()->targetId);
                    if (forceWeapon) {
                        forceWeapon.value()->attached = true;
                    }
                    auto forceWeaponMovementComponent =
                        componentManager.getComponent<MovementComponent>(
                            frontComponent.value()->targetId);
                    if (forceWeaponMovementComponent) {
                        forceWeaponMovementComponent.value()->move = false;
                    }
                }
            }
            return true;
        } else if (playerMissile1) {
            if (enemy2 || enemyMissile2) {
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                    entitiesToRemove.end()) {
                    entitiesToRemove.push_back(entityId1);
                }
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                    entitiesToRemove.end()) {
                    if (rand() % 10 == 0) {
                        auto posEnemy =
                            componentManager.getComponent<PositionComponent>(entityId2);
                        if (posEnemy) {
                            Entity weapon =
                                server->GetEntityFactory().createPowerUpBlueLaserCrystal(
                                    entityManager, componentManager, posEnemy.value()->x,
                                    posEnemy.value()->y);
                            entitiesToAdd.push_back(weapon.getId());
                        }
                    }
                    entitiesToRemove.push_back(entityId2);
                }
                int playerId = playerMissile1.value()->playerId;
                if (auto playerScore = componentManager.getComponent<ScoreComponent>(playerId)) {
                    playerScore.value()->score += 100;
                }
                r_type::net::Message<TypeMessage> updScoreMsg;
                updScoreMsg.header.id = TypeMessage::UpdateInfoBar;
                updScoreMsg << server->UpdateInfoBar(playerId);
                server->MessageClient(server->getClientById(server->_deqConnections,
                                          server->GetPlayerClientId(playerId)),
                    updScoreMsg);
            }
            return true;
        } else if (forceMissile1) {
            if (enemy2 || enemyMissile2) {
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                    entitiesToRemove.end()) {
                    entitiesToRemove.push_back(entityId1);
                }
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                    entitiesToRemove.end()) {
                    auto posEnemy = componentManager.getComponent<PositionComponent>(entityId2);
                    if (rand() % 10 == 0) {
                        auto posEnemy =
                            componentManager.getComponent<PositionComponent>(entityId2);
                        if (posEnemy) {
                            Entity weapon =
                                server->GetEntityFactory().createPowerUpBlueLaserCrystal(
                                    entityManager, componentManager, posEnemy.value()->x,
                                    posEnemy.value()->y);
                            entitiesToAdd.push_back(weapon.getId());
                        }
                    }
                    entitiesToRemove.push_back(entityId2);
                }
                auto weapon = componentManager.getComponent<ForceWeaponComponent>(
                    forceMissile1.value()->forceId);
                if (weapon) {
                    int playerId = weapon.value()->playerId;
                    if (auto playerScore =
                            componentManager.getComponent<ScoreComponent>(playerId)) {
                        playerScore.value()->score += 100;
                    }
                    r_type::net::Message<TypeMessage> updScoreMsg;
                    updScoreMsg.header.id = TypeMessage::UpdateInfoBar;
                    updScoreMsg << server->UpdateInfoBar(playerId);
                    server->MessageClient(server->getClientById(server->_deqConnections,
                                              server->GetPlayerClientId(playerId)),
                        updScoreMsg);
                }
            }
            return true;
        } else if (forceWeapon1) {
            if (enemyMissile2) {
                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                    entitiesToRemove.end()) {
                    entitiesToRemove.push_back(entityId2);
                }
                std::cout << "force weapon collided with enemy missile" << std::endl;
            }
            return true;
        }
        return false;
    }

    /**
     * @brief Updates the collision status of entities in the game.
     *
     * This function checks for collisions between entities and handles the consequences
     * of those collisions, such as updating health, removing entities, and adding new
     * entities. It also handles entities that go off-screen.
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
                    if (collisionAction(server, componentManager, entityManager, entitiesToRemove,
                            entitiesToAdd, entityId1, entityId2) == false) {
                        collisionAction(server, componentManager, entityManager, entitiesToRemove,
                            entitiesToAdd, entityId2, entityId1);
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
            if (auto playerComponent = componentManager.getComponent<PlayerComponent>(entityId)) {
                continue;
            }
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
     * @brief Updates the animations of entities and sends messages to clients if animations
     * have changed.
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
            _animationSystem->AnimationEntities(
                componentManager, entityManager, 0.2, server->_endOfLevel);
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
     * entities. It retrieves all entities and checks if they can shoot. If an entity can
     * shoot, it sends a message to all clients to create an enemy missile and sets the
     * entity's canShoot flag to false.
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
                        auto weapon =
                            componentManager.getComponent<ForceWeaponComponent>(entityId);
                        if (weapon) {
                            if (!weapon.value()->attached) {
                                Entity missile = server->GetEntityFactory().createForceMissile(
                                    entityManager, componentManager, entityId);
                                r_type::net::Message<TypeMessage> weaponMissileMsg;
                                weaponMissileMsg.header.id = TypeMessage::CreateEntityMessage;
                                weaponMissileMsg << server->InitiatePlayerMissile(missile.getId());
                                server->MessageAllClients(weaponMissileMsg);
                            }
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
        if (std::chrono::duration_cast<std::chrono::seconds>(server->GetClock() - _WallSpawnTime)
                .count() > _gameParameters.spawnTimeWall) {
            SpawnEntity(server, entityManager, componentManager, _gameParameters.nbrOfWall,
                EntityFactory::EnemyType::Wall);
            _WallSpawnTime = server->GetClock();
        }
    }

    /**
     * @brief Handles the spawning of entities for Level Two.
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
    void LevelTwo(r_type::net::AServer<T> *server, ComponentManager &componentManager,
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
        if (std::chrono::duration_cast<std::chrono::seconds>(server->GetClock() - _WallSpawnTime)
                .count() > _gameParameters.spawnTimeWall) {
            SpawnEntity(server, entityManager, componentManager, _gameParameters.nbrOfWall,
                EntityFactory::EnemyType::Wall);
            _WallSpawnTime = server->GetClock();
        }
    }

    /**
     * @brief Handles the spawning of entities for Level Three.
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
    void LevelThree(r_type::net::AServer<T> *server, ComponentManager &componentManager,
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
        if (std::chrono::duration_cast<std::chrono::seconds>(server->GetClock() - _WallSpawnTime)
                .count() > _gameParameters.spawnTimeWall) {
            SpawnEntity(server, entityManager, componentManager, _gameParameters.nbrOfWall,
                EntityFactory::EnemyType::Wall);
            _WallSpawnTime = server->GetClock();
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
            int i = 0;
            int posX = 100;
            int posY = static_cast<int>((rand() % 70) + 10);
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
            int i = 0;
            int posX = 99;
            int posY = static_cast<int>((rand() % 70) + 10);
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
        case EntityFactory::EnemyType::Wall: {
            int i = 0;
            int posX = 99;
            int posY = static_cast<int>((rand() % 70) + 10);

            while (i < nbrOfEnemy) {
                Entity wall = server->GetEntityFactory().createWall(
                    entityManager, componentManager, posX, posY);
                posX += 5;
                posY += (static_cast<int>(rand() % 20) - static_cast<int>(rand() % 10));

                if (posY > 90)
                    posY = static_cast<int>((rand() % 70) + 10);
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::CreateEntityMessage;
                msg << server->FormatEntityInformation(wall.getId());
                server->MessageAllClients(msg);
                i++;
            }
        } break;
        case EntityFactory::EnemyType::Boss: {
            server->InitBoss(server);
        } break;
        default:
            break;
        }
    }

    /**
     * @brief Get the Entity Back Ground object
     *
     * @param server
     * @param entityManager
     * @param componentManager
     * @return EntityInformation
     */
    EntityInformation GetEntityBackGround(r_type::net::AServer<T> *server,
        EntityManager &entityManager, ComponentManager &componentManager) override
    {
        EntityInformation entityInfo;
        auto background = componentManager.getComponentMap<BackgroundComponent>();
        if (background) {
            for (auto &pair : **background) {
                int entityId = pair.first;
                auto &backgroundComponent = pair.second;
                if (auto backgroundInfo =
                        std::any_cast<BackgroundComponent>(&backgroundComponent)) {
                    return server->FormatEntityInformation(entityId);
                }
            }
        } else {
            return InitiateBackground(server, entityManager, componentManager);
        }
        return entityInfo;
    }

    /**
     * @brief Changes the background in the game by removing the current background entity and
     * creating a new one.
     *
     * This function sends messages to all clients to destroy the current background entity and
     * create a new one.
     *
     * @tparam T The type of the server.
     * @param server Pointer to the server instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param componentManager Reference to the ComponentManager instance.
     */
    void ChangeBackground(r_type::net::AServer<T> *server, EntityManager &entityManager,
        ComponentManager &componentManager) override
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::DestroyEntityMessage;
        auto background = componentManager.getComponentMap<BackgroundComponent>();
        if (background) {
            for (auto &pair : **background) {
                int entityId = pair.first;
                auto &backgroundComponent = pair.second;
                if (auto backgroundInfo =
                        std::any_cast<BackgroundComponent>(&backgroundComponent)) {
                    msg << background;
                    server->MessageAllClients(msg);
                    componentManager.removeEntityFromAllComponents(entityId);
                    entityManager.removeEntity(entityId);
                    msg.header.id = TypeMessage::CreateEntityMessage;
                    msg << InitiateBackground(server, entityManager, componentManager);
                    server->MessageAllClients(msg);
                }
            }
        }
    }

    GameState GetLevel() override { return _gameParameters.levelType; }

    /**
     * @brief Initializes a background entity.
     *
     * The function creates and returns information about the background entity.
     *
     * @return EntityInformation The information of the background entity.
     */
    EntityInformation InitiateBackground(r_type::net::AServer<T> *server,
        EntityManager &entityManager, ComponentManager &componentManager) override
    {
        EntityInformation entityInfo;
        Entity background = server->GetEntityFactory().backgroundFactory(
            entityManager, componentManager, _gameParameters.levelType);
        entityInfo.uniqueID = background.getId();
        auto sprite = componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto backgroundPos = componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto animation = componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (sprite) {
            entityInfo.spriteData = *(sprite.value());
            entityInfo.vPos.x = backgroundPos.value()->x;
            entityInfo.vPos.y = backgroundPos.value()->y;
            if (animation) {
                entityInfo.ratio.x =
                    (animation.value()->dimension.x * sprite.value()->scale.x) / SCREEN_WIDTH;
                entityInfo.ratio.y =
                    (animation.value()->dimension.y * sprite.value()->scale.y) / SCREEN_HEIGHT;
                entityInfo.animationComponent.dimension = animation.value()->dimension;
                entityInfo.animationComponent.offset = animation.value()->offset;
            }
        }
        return entityInfo;
    }

    /**
     * @brief Sets the game difficulty based on the provided game parameters.
     *
     * This function sets the game difficulty based on the provided game parameters.
     *
     * @param gameParameters The game parameters to set the difficulty.
     */
    void SetGameParameters(GameParameters gameParameters) { _gameParameters = gameParameters; }

    /**
     * @brief Changes the level of the game based on the provided game state.
     *
     * This function changes the level of the game based on the provided game state.
     *
     * @param state The game state to change the level to.
     */
    void ChangeLevel(GameState state) override { _gameParameters.levelType = state; }

  protected:
    /**
     * @brief A shared pointer to the MoveSystem instance.
     *
     * This member variable holds a shared pointer to an instance of the MoveSystem class,
     * which is responsible for handling movement logic within the system. Using a shared
     * pointer ensures that the MoveSystem instance is properly managed and its lifetime
     * is tied to the number of references to it.
     */
    std::shared_ptr<MoveSystem> _moveSystem;
    /**
     * @brief A shared pointer to the CollisionSystem.
     *
     * This member variable holds a shared pointer to an instance of the CollisionSystem,
     * which is responsible for handling collision detection and response within the game.
     * Using a shared pointer ensures that the CollisionSystem instance is properly managed
     * and its memory is automatically deallocated when no longer in use.
     */
    std::shared_ptr<CollisionSystem> _collisionSystem;
    /**
     * @brief A shared pointer to the AnimationSystem.
     *
     * This member variable holds a shared pointer to an instance of the AnimationSystem.
     * The AnimationSystem is responsible for managing and updating animations within the game.
     * Using a shared pointer ensures that the AnimationSystem instance is properly managed
     * and its lifetime is controlled, preventing memory leaks and dangling pointers.
     */
    std::shared_ptr<AnimationSystem> _animationSystem;
    /**
     * @brief A shared pointer to an instance of AutoFireSystem.
     *
     * This member variable holds a shared pointer to an AutoFireSystem object,
     * which is responsible for managing the automatic firing mechanism in the game.
     * The use of std::shared_ptr ensures that the AutoFireSystem instance is
     * properly managed and deallocated when no longer in use.
     */
    std::shared_ptr<AutoFireSystem> _autoFireSystem;

    /**
     * @brief Represents the time point at which a basic monster is spawned.
     *
     * This variable is initialized to the current system time using
     * std::chrono::system_clock::now(). It is used to track the spawn time
     * of a basic monster in the game.
     */
    std::chrono::system_clock::time_point _basicMonsterSpawnTime =
        std::chrono::system_clock::now();
    /**
     * @brief Represents the time point when the shooter enemy is spawned.
     *
     * This variable is initialized to the current system time using
     * std::chrono::system_clock::now(). It is used to track the exact
     * moment when the shooter enemy is spawned in the game.
     */
    std::chrono::system_clock::time_point _shooterEnemySpawnTime =
        std::chrono::system_clock::now();
    /**
     * @brief Stores the time point when the wall was spawned.
     *
     * This member variable holds the time point, using the system clock,
     * at which the wall was spawned. It is initialized to the current time
     * when the object is created.
     */
    std::chrono::system_clock::time_point _WallSpawnTime = std::chrono::system_clock::now();
    /**
     * @brief The time point at which the third type of monster is spawned.
     *
     * This member variable holds the spawn time for the third type of monster
     * using the system clock's time point. It is used to schedule or track
     * when the third type of monster should appear in the game.
     */
    std::chrono::system_clock::time_point _spawnTimeMonsterThree;

    /**
     * @brief Holds the parameters for the game configuration.
     *
     * This member variable stores an instance of the GameParameters class,
     * which contains various settings and configurations for the game.
     */
    GameParameters _gameParameters;
};
} // namespace r_type