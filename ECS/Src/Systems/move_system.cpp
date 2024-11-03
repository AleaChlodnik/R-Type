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
        case MovementType::SWEEPING: {
            float oscillationAmplitude = 2.8f;
            float oscillationSpeed = 0.1f;
            float segmentDistance = 2.4f;

            auto prevSegmentId = entityId - 1;
            if (auto prevPosition =
                    componentManager.getComponent<PositionComponent>(prevSegmentId)) {
                position.value()->y = prevPosition.value()->y - segmentDistance;
            }

            position.value()->y -=
                (sin(movement.value()->index * oscillationSpeed) * oscillationAmplitude);

            position.value()->x -= velocity.value()->x;

            movement.value()->index += 1;
        } break;
        case MovementType::NONE: {
            break;
        } break;
        }
    }
}
