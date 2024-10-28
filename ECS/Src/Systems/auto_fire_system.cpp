/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** auto_fire_system
*/

#include <Systems/auto_fire_system.hpp>

void AutoFireSystem::handleAutoFire(
    ComponentManager &componentManager, EntityManager &entityManager)
{
    auto now = std::chrono::system_clock::now();
    auto entities = entityManager.getAllEntities();
    if (entities.empty())
        return;

    for (auto &entity : entities) {
        int entityId = entity.getId();
        auto shootInfo = componentManager.getComponent<ShootComponent>(entityId);
        if (shootInfo) {
            if (now >= shootInfo.value()->nextShootTime) {
                shootInfo.value()->canShoot = true;
                shootInfo.value()->nextShootTime = now + shootInfo.value()->cooldownTime;
            }
        }
    }
}
