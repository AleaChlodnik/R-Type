/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#include <Systems/move_system.hpp>

void MoveSystem::moveEntities(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto entities = entityManager.getAllEntities();
    if (entities.empty())
        return;

    for (auto &entity : entities) {
        int entityId = entity.getId();
        auto position = componentManager.getComponent<PositionComponent>(entityId);
        auto velocity = componentManager.getComponent<VelocityComponent>(entityId);
        if (position && velocity) {
            position.value()->x += velocity.value()->x;
        }
    }
}
