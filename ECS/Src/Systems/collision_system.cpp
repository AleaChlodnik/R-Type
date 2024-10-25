/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#include <Systems/collision_system.hpp>
#include <macros.hpp>
#include <vector>

void CollisionSystem::removeCollidedEntity(ComponentManager &componentManager, int entityId1,
    int entityId2, std::vector<int> &entitiesToRemove)
{
    // Checking components for entity1 and entity2
    auto player1 = componentManager.getComponent<PlayerComponent>(entityId1);
    auto playerMissile1 = componentManager.getComponent<PlayerMissileComponent>(entityId1);
    auto enemy1 = componentManager.getComponent<EnemyComponent>(entityId1);
    auto enemyMissile1 = componentManager.getComponent<EnemyMissileComponent>(entityId1);
    auto basicMonster1 = componentManager.getComponent<BasicMonsterComponent>(entityId1);

    auto player2 = componentManager.getComponent<PlayerComponent>(entityId2);
    auto playerMissile2 = componentManager.getComponent<PlayerMissileComponent>(entityId2);
    auto enemy2 = componentManager.getComponent<EnemyComponent>(entityId2);
    auto enemyMissile2 = componentManager.getComponent<EnemyMissileComponent>(entityId2);
    auto basicMonster2 = componentManager.getComponent<BasicMonsterComponent>(entityId2);

    // Determine which entities need to be removed based on components
    if (player1) {
        if (enemy2 || enemyMissile2) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId2);
        } else if (basicMonster2) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
        }
    }
    if (playerMissile1) {
        if (enemy2 || basicMonster2) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId2);
        }
        if (enemyMissile2) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId2);
        }
    }
    if (player2) {
        if (enemy1 || enemyMissile1) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId2);
        } else if (basicMonster1) {
            entitiesToRemove.push_back(entityId2);
        }
    }
    if (playerMissile2) {
        if (enemy1 || basicMonster1) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
        }
        if (enemyMissile1) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId1) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId1);
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId2) ==
                entitiesToRemove.end())
                entitiesToRemove.push_back(entityId2);
        }
    }
}

bool CollisionSystem::checkOffScreen(ComponentManager &componentManager, int entityId)
{
    auto pos = componentManager.getComponent<PositionComponent>(entityId);
    auto hitbox = componentManager.getComponent<HitboxComponent>(entityId);

    if (pos && hitbox) {
        float left = ((pos.value()->x / 100) * SCREEN_WIDTH) - (hitbox.value()->w / 2);
        float right = ((pos.value()->x / 100) * SCREEN_WIDTH) + (hitbox.value()->w / 2);
        float top = ((pos.value()->y / 100) * SCREEN_HEIGHT) - (hitbox.value()->h / 2);
        float bottom = ((pos.value()->y / 100) * SCREEN_HEIGHT) + (hitbox.value()->h / 2);

        // Check if the entity is out of screen boundaries
        return (right < 0 || left > SCREEN_WIDTH || bottom < 0 || top > SCREEN_HEIGHT);
    }
    return false;
}

bool CollisionSystem::checkCollision(
    ComponentManager &componentManager, int entityId1, int entityId2)
{
    auto pos1 = componentManager.getComponent<PositionComponent>(entityId1);
    auto pos2 = componentManager.getComponent<PositionComponent>(entityId2);
    auto hitbox1 = componentManager.getComponent<HitboxComponent>(entityId1);
    auto hitbox2 = componentManager.getComponent<HitboxComponent>(entityId2);

    if (pos1 && pos2 && hitbox1 && hitbox2) {
        float left1 = ((pos1.value()->x / 100) * SCREEN_WIDTH) - (hitbox1.value()->w / 2);
        float right1 = ((pos1.value()->x / 100) * SCREEN_WIDTH) + (hitbox1.value()->w / 2);
        float top1 = ((pos1.value()->y / 100) * SCREEN_HEIGHT) - (hitbox1.value()->h / 2);
        float bottom1 = ((pos1.value()->y / 100) * SCREEN_HEIGHT) + (hitbox1.value()->h / 2);

        float left2 = ((pos2.value()->x / 100) * SCREEN_WIDTH) - (hitbox2.value()->w / 2);
        float right2 = ((pos2.value()->x / 100) * SCREEN_WIDTH) + (hitbox2.value()->w / 2);
        float top2 = ((pos2.value()->y / 100) * SCREEN_HEIGHT) - (hitbox2.value()->h / 2);
        float bottom2 = ((pos2.value()->y / 100) * SCREEN_HEIGHT) + (hitbox2.value()->h / 2);

        bool collision =
            !(right1 <= left2 || left1 >= right2 || bottom1 <= top2 || top1 >= bottom2);

        return collision;
    }
    return false;
}

void CollisionSystem::handleCollisions(
    ComponentManager &componentManager, EntityManager &entityManager)
{
    auto entities = entityManager.getAllEntities();
    std::vector<int> entitiesToRemove;

    // Check for collisions between entities
    for (size_t i = 0; i < entities.size(); ++i) {
        int entityId1 = entities[i].getId();
        for (size_t j = i + 1; j < entities.size(); ++j) {
            int entityId2 = entities[j].getId();
            if (checkCollision(componentManager, entityId1, entityId2)) {
                removeCollidedEntity(componentManager, entityId1, entityId2, entitiesToRemove);
            }
        }
    }

    // Check for entities that are off-screen
    for (const auto &entity : entities) {
        int entityId = entity.getId();
        if (checkOffScreen(componentManager, entityId)) {
            if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entityId) ==
                entitiesToRemove.end()) {
                entitiesToRemove.push_back(entityId);
            }
        }
    }

    for (int entityId : entitiesToRemove) {
        componentManager.removeEntityFromAllComponents(entityId);
        entityManager.removeEntity(entityId);
    }
}
