/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#include <Systems/collision_system.hpp>

bool CollisionSystem::checkCollision(
    ComponentManager &componentManager, int entityId1, int entityId2)
{
    auto pos1 = componentManager.getComponent<PositionComponent>(entityId1);
    auto pos2 = componentManager.getComponent<PositionComponent>(entityId2);
    auto hitbox1 = componentManager.getComponent<HitboxComponent>(entityId1);
    auto hitbox2 = componentManager.getComponent<HitboxComponent>(entityId2);

    if (pos1 && pos2 && hitbox1 && hitbox2) {
        int left1 = pos1.value()->x;
        int right1 = pos1.value()->x + hitbox1.value()->w;
        int top1 = pos1.value()->y;
        int bottom1 = pos1.value()->y + hitbox1.value()->h;

        int left2 = pos2.value()->x;
        int right2 = pos2.value()->x + hitbox2.value()->w;
        int top2 = pos2.value()->y;
        int bottom2 = pos2.value()->y + hitbox2.value()->h;

        if (right1 <= left2 || left1 >= right2 || bottom1 <= top2 || top1 >= bottom2)
            return false;
        else
            return true;
    }
    return false;
}

void CollisionSystem::handleCollisions(
    ComponentManager &componentManager, EntityManager &entityManager)
{
    auto entities = entityManager.getAllEntities();
    for (size_t i = 0; i < entities.size(); ++i) {
        int entityId1 = entities[i].getId();
        for (size_t j = i + 1; j < entities.size(); ++j) {
            int entityId2 = entities[j].getId();
            if (checkCollision(componentManager, entityId1, entityId2)) {
                removeCollidedEntity(componentManager, entityManager, entityId1, entityId2);
            }
        }
    }
}

void CollisionSystem::removeCollidedEntity(
    ComponentManager &componentManager, EntityManager &entityManager, int entityId1, int entityId2)
{
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

    if (player1) {
        if (enemy2 || enemyMissile2) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in enemy2 || enemyMissile2 removed"
                      << std::endl; /////////////////////////////////
            entityManager.removeEntity(entityId2);
            std::cout << "entityId2 in enemy2 || enemyMissile2 removed"
                      << std::endl; /////////////////////////////////
        }
        if (basicMonster2) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in basicMonster2 removed"
                      << std::endl; /////////////////////////////////
        }
    }
    if (playerMissile1) {
        if (enemy2 || basicMonster2) {
            entityManager.removeEntity(entityId2);
            std::cout << "entityId2 in enemy2 || enemyMissile2 removed"
                      << std::endl; /////////////////////////////////
        }
        if (enemyMissile2) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in enemyMissile2 removed"
                      << std::endl; /////////////////////////////////
            entityManager.removeEntity(entityId2);
            std::cout << "entityId2 in enemyMissile2 removed"
                      << std::endl; /////////////////////////////////
        }
    }
    if (player2) {
        if (enemy1 || enemyMissile1) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in enemy1 || enemyMissile1 removed"
                      << std::endl; /////////////////////////////////
            entityManager.removeEntity(entityId2);
            std::cout << "entityId1 in enemy2 || enemyMissile1 removed"
                      << std::endl; /////////////////////////////////
        }
        if (basicMonster1) {
            entityManager.removeEntity(entityId2);
            std::cout << "entityId2 in basicMonster1 removed"
                      << std::endl; /////////////////////////////////
        }
    }
    if (playerMissile2) {
        if (enemy1 || basicMonster1) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in enemy1 || basicMonster1 removed"
                      << std::endl; /////////////////////////////////
        }
        if (enemyMissile1) {
            entityManager.removeEntity(entityId1);
            std::cout << "entityId1 in enemyMissile1 removed"
                      << std::endl; /////////////////////////////////
            entityManager.removeEntity(entityId2);
            std::cout << "entityId2 in enemyMissile1 removed"
                      << std::endl; /////////////////////////////////
        }
    }
}
