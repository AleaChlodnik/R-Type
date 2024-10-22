/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** hitbox_tmp
*/

#include "hitbox_tmp.hpp"

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
                entityLeft = (entityPos.value()->x / 100.0f) * 1920 -
                    (((entityHitbox.value()->w / 100.0f) * 1920) / 2);
                entityRight = (entityPos.value()->x / 100.0f) * 1920 +
                    (((entityHitbox.value()->w / 100.0f) * 1920) / 2);
                entityTop = (entityPos.value()->y / 100.0f) * 1080 -
                    (((entityHitbox.value()->h / 100.0f) * 1080) / 2);
                entityBottom = (entityPos.value()->y / 100.0f) * 1080 +
                    (((entityHitbox.value()->h / 100.0f) * 1080) / 2);

                if (!(descRight < entityLeft || descLeft > entityRight || descBottom < entityTop ||
                        descTop > entityBottom)) {
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
    auto descPos = componentManager.getComponent<PositionComponent>(entityId);
    auto descHitbox = componentManager.getComponent<HitboxComponent>(entityId);
    if (!descPos || !descHitbox)
        return -1;

    float descLeft =
        (descPos.value()->x / 100.0f) * 1920 - (((descHitbox.value()->w / 100.0f) * 1920) / 2);
    float descRight =
        (descPos.value()->x / 100.0f) * 1920 + (((descHitbox.value()->w / 100.0f) * 1920) / 2);
    float descTop =
        (descPos.value()->y / 100.0f) * 1080 - (((descHitbox.value()->h / 100.0f) * 1080) / 2);
    float descBottom =
        (descPos.value()->y / 100.0f) * 1080 + (((descHitbox.value()->h / 100.0f) * 1080) / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, entityId);
}

int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager)
{
    float descLeft =
        (desc.vPos.x / 100.0f) * 1920 - (((desc.spriteData.dimension.x / 100.0f) * 1920) / 2);
    float descRight =
        (desc.vPos.x / 100.0f) * 1920 + (((desc.spriteData.dimension.x / 100.0f) * 1920) / 2);
    float descTop =
        (desc.vPos.y / 100.0f) * 1080 - (((desc.spriteData.dimension.y / 100.0f) * 1080) / 2);
    float descBottom =
        (desc.vPos.y / 100.0f) * 1080 + (((desc.spriteData.dimension.y / 100.0f) * 1080) / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, desc.uniqueID);
}
