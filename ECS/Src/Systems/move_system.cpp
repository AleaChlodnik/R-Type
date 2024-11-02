/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#include <Systems/move_system.hpp>
#include <cmath>

void MoveSystem::moveEntities(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto entities = entityManager.getAllEntities();
    if (entities.empty())
        return;

    for (auto &entity : entities) {

        int entityId = entity.getId();
        moveEntity(componentManager, entityId);
    }
}

void MoveSystem::moveEntity(ComponentManager &componentManager, int entityId)
{
    auto position = componentManager.getComponent<PositionComponent>(entityId);
    auto velocity = componentManager.getComponent<VelocityComponent>(entityId);
    auto movement = componentManager.getComponent<MovementComponent>(entityId);
    if (movement && movement.value()->move == true) {
        switch (movement.value()->movementType) {
        case MovementType::WIGGLE: {
            position.value()->y += cos(movement.value()->index * 0.1 * M_PI);
            position.value()->x += velocity.value()->x;
            movement.value()->index += 1;
        } break;
        case MovementType::DIAGONAL: {
            position.value()->y += cos(movement.value()->index * 0.1 * M_PI) / 2;
            position.value()->x += velocity.value()->x;
            movement.value()->index += 1;
        } break;
        case MovementType::CIRCLE: {
            // position.value()->y += velocity.value()->y;
        } break;
        case MovementType::STRAIGHT: {
            position.value()->x += velocity.value()->x;
            position.value()->y += velocity.value()->y;
        } break;
        }
    }
}
