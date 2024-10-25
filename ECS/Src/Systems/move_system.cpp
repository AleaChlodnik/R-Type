/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#include <Systems/move_system.hpp>

void MoveSystem::moveEntities(
    ComponentManager &componentManager, EntityManager &entityManager, float deltaTime)
{
    auto entities = entityManager.getAllEntities();
    if (entities.empty())
        return;

    for (auto &entity : entities) {
        int entityId = entity.getId();
        auto pos = componentManager.getComponent<PositionComponent>(entityId);
        auto vel = componentManager.getComponent<VelocityComponent>(entityId);
        if (pos && vel) {
            auto enemy = componentManager.getComponent<EnemyComponent>(entityId);
            auto basicMonster = componentManager.getComponent<BasicMonsterComponent>(entityId);
            auto playerMissile = componentManager.getComponent<PlayerMissileComponent>(entityId);
            auto enemyMissile = componentManager.getComponent<EnemyMissileComponent>(entityId);

            if (enemy || basicMonster || enemyMissile) {
                pos.value()->x -= 2;
            }

            if (playerMissile) {
                pos.value()->x += 2;
            }

        }
    }
}
