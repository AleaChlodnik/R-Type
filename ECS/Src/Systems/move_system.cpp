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
        auto direction = componentManager.getComponent<DirectionComponent>(entityId);
        if (position && velocity && direction) {
            if (direction.value()->direction == Direction::LEFT) {
                position.value()->x -= velocity.value()->speed;
            } else if (direction.value()->direction == Direction::RIGHT) {
                position.value()->x += velocity.value()->speed;
            }
        }
    }
}
