/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#include <Systems/collision_system.hpp>
#include <macros.hpp>
#include <vector>

bool CollisionSystem::checkOffScreen(ComponentManager &componentManager, int entityId)
{
    auto pos = componentManager.getComponent<PositionComponent>(entityId);
    auto hitbox = componentManager.getComponent<HitboxComponent>(entityId);

    if (pos && hitbox) {
        float left = ((pos.value()->x / 100) * SCREEN_WIDTH) - (hitbox.value()->w / 2);
        float right = ((pos.value()->x / 100) * SCREEN_WIDTH) + (hitbox.value()->w / 2);
        float top = ((pos.value()->y / 100) * SCREEN_HEIGHT) - (hitbox.value()->h / 2);
        float bottom = ((pos.value()->y / 100) * SCREEN_HEIGHT) + (hitbox.value()->h / 2);

        return (right < 0 || left > (SCREEN_WIDTH * 1.50) || bottom < 0 ||
            top > (SCREEN_HEIGHT * 1.50));
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
