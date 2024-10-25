/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** hitbox_tmp
*/

#include "hitbox_tmp.hpp"
#include <macros.hpp>

static int CheckCollisionLogic(float descLeft, float descRight, float descTop, float descBottom,
    ComponentManager componentManager, EntityManager entityManager, int entityId)
{
    float entityLeft, entityRight, entityTop, entityBottom;
    const std::vector<Entity> entities = entityManager.getAllEntities();

    for (const auto &entity : entities) {
        if (entity.getId() != entityId && entity.getId() != 1) {
            auto entityPos = componentManager.getComponent<PositionComponent>(entity.getId());
            auto entityHitbox = componentManager.getComponent<HitboxComponent>(entity.getId());
            if (entityPos && entityHitbox) {
                entityLeft = ((entityPos.value()->x / 100) * SCREEN_WIDTH) - (entityHitbox.value()->w / 2);
                entityRight =
                    ((entityPos.value()->x / 100) * SCREEN_WIDTH) + (entityHitbox.value()->w / 2);
                entityTop = ((entityPos.value()->y / 100) * SCREEN_HEIGHT) - (entityHitbox.value()->h / 2);
                entityBottom =
                    ((entityPos.value()->y / 100) * SCREEN_HEIGHT) + (entityHitbox.value()->h / 2);

                if ((entityLeft <= descRight && entityRight >= descLeft) &&
                    (entityTop <= descBottom && entityBottom >= descTop)) {
                    return entity.getId();
                }
            }
        }
    }
    return -1;
}

int CheckEntityPosition(
    uint32_t entityId, ComponentManager componentManager, EntityManager entityManager)
{
    float descLeft, descTop, descBottom, descRight;
    auto descPos = componentManager.getComponent<PositionComponent>(entityId);
    auto descHitbox = componentManager.getComponent<HitboxComponent>(entityId);
    if (!descPos || !descHitbox)
        return -1;

    descLeft = ((descPos.value()->x / 100) * SCREEN_WIDTH) - (descHitbox.value()->w / 2);
    descRight = ((descPos.value()->x / 100) * SCREEN_WIDTH) + (descHitbox.value()->w / 2);
    descTop = ((descPos.value()->y / 100) * SCREEN_HEIGHT) - (descHitbox.value()->h / 2);
    descBottom = ((descPos.value()->y / 100) * SCREEN_HEIGHT) + (descHitbox.value()->h / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, entityId);
}

int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager)
{
    float descLeft, descRight, descTop, descBottom;

    descLeft = ((desc.vPos.x / 100) * SCREEN_WIDTH) - (desc.spriteData.dimension.x / 2);
    descRight = ((desc.vPos.x / 100) * SCREEN_WIDTH) + (desc.spriteData.dimension.x / 2);
    descTop = ((desc.vPos.y / 100) * SCREEN_HEIGHT) - (desc.spriteData.dimension.y / 2);
    descBottom = ((desc.vPos.y / 100) * SCREEN_HEIGHT) + (desc.spriteData.dimension.y / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, desc.uniqueID);
}
