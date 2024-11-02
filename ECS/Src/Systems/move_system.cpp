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
        auto forceWeapon = componentManager.getComponent<ForceWeaponComponent>(entityId);
        if (forceWeapon) {
            if (forceWeapon.value()->attached == false) {
                moveEntity(componentManager, entityId);
            }
        } else {
            moveEntity(componentManager, entityId);
        }
    }
}

void MoveSystem::moveEntity(ComponentManager &componentManager, int entityId)
{
    auto position = componentManager.getComponent<PositionComponent>(entityId);
    auto velocity = componentManager.getComponent<VelocityComponent>(entityId);
    auto movement = componentManager.getComponent<MovementComponent>(entityId);
    if (movement) {
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
        }
    } else {
        if (position && velocity) {
            position.value()->x += velocity.value()->x;
        }
    }
}
