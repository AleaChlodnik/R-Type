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

    void CollisionUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) override
    {
        std::vector<int> entitiesToRemove;
        auto beforeCollisioneEntities = entityManager.getAllEntities();
        for (size_t i = 0; i < beforeCollisioneEntities.size(); ++i) {
            int entityId1 = beforeCollisioneEntities[i].getId();
            for (size_t j = i + 1; j < beforeCollisioneEntities.size(); ++j) {
                int entityId2 = beforeCollisioneEntities[j].getId();
                if (_collisionSystem.get()->checkCollision(
                        componentManager, entityId1, entityId2)) {
                    auto shooterEnemy1 = componentManager.getComponent<ShootComponent>(entityId1);
                    auto enemyMissile1 =
                        componentManager.getComponent<EnemyMissileComponent>(entityId1);
                    auto basicMonster1 =
                        componentManager.getComponent<BasicMonsterComponent>(entityId1);
                    auto shooterEnemy2 = componentManager.getComponent<ShootComponent>(entityId2);
                    auto enemyMissile2 =
                        componentManager.getComponent<EnemyMissileComponent>(entityId2);
                    auto basicMonster2 =
                        componentManager.getComponent<BasicMonsterComponent>(entityId2);
                    if (auto player1 = componentManager.getComponent<PlayerComponent>(entityId1)) {
                        if (auto playerHealth =
                                componentManager.getComponent<HealthComponent>(entityId1)) {
                            if (shooterEnemy2 || enemyMissile2) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                                playerHealth.value()->health -= 1;
                            }
                            if (basicMonster2) {
                                playerHealth.value()->health -= 1;
                            }
                            if (playerHealth.value()->health <= 0) {
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
                    } else if (auto playerMissile1 =
                                   componentManager.getComponent<PlayerMissileComponent>(
                                       entityId1)) {
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
                    } else if (auto player2 =
                                   componentManager.getComponent<PlayerComponent>(entityId2)) {
                        if (auto playerHealth =
                                componentManager.getComponent<HealthComponent>(entityId2)) {
                            if (shooterEnemy1 || enemyMissile1) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId1) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId1);
                                }
                                playerHealth.value()->health -= 1;
                            }
                            if (basicMonster1) {
                                playerHealth.value()->health -= 1;
                            }
                            if (playerHealth.value()->health <= 0) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                            }
                            r_type::net::Message<TypeMessage> updLivesMsg;
                            updLivesMsg.header.id = TypeMessage::UpdateInfoBar;
                            updLivesMsg << server->UpdateInfoBar(entityId1);
                            server->MessageClient(server->getClientById(server->_deqConnections,
                                                      server->GetPlayerClientId(entityId2)),
                                updLivesMsg);
                        }
                    } else if (auto playerMissile2 =
                                   componentManager.getComponent<PlayerMissileComponent>(
                                       entityId2)) {
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
                    } else {
                        continue;
                    }
                }
            }
        }
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
            _animationSystem->AnimationEntities(componentManager, entityManager, 0.5);
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

  protected:
    std::shared_ptr<MoveSystem> _moveSystem;
    std::shared_ptr<CollisionSystem> _collisionSystem;
    std::shared_ptr<AnimationSystem> _animationSystem;
    std::shared_ptr<AutoFireSystem> _autoFireSystem;
};
} // namespace r_type