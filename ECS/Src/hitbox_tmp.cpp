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
    float playerLeft, playerRight, playerTop, playerBottom;
    const std::vector<Entity> entities = entityManager.getAllEntities();

    for (const auto &entity : entities) {
        if (entity.getId() != entityId && entity.getId() != 1) {
            auto playerPos = componentManager.getComponent<PositionComponent>(entity.getId());
            auto playerHitbox = componentManager.getComponent<HitboxComponent>(entity.getId());
            if (playerPos && playerHitbox) {

                playerLeft = (playerPos.value()->x / 100) - ((playerHitbox.value()->w / 100) / 2);
                playerRight = (playerPos.value()->x / 100) + ((playerHitbox.value()->w / 100) / 2);
                playerTop = (playerPos.value()->y / 100) - ((playerHitbox.value()->h / 100) / 2);
                playerBottom = (playerPos.value()->y / 100) + ((playerHitbox.value()->h / 100) / 2);

                if (!(descRight < playerLeft || descLeft > playerRight || descBottom < playerTop ||
                        descTop > playerBottom)) {
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

    float descLeft = (descPos.value()->x / 100) - ((descHitbox.value()->w / 100) / 2);
    float descRight = (descPos.value()->x / 100) + ((descHitbox.value()->w / 100) / 2);
    float descTop = (descPos.value()->y / 100) - ((descHitbox.value()->h / 100) / 2);
    float descBottom = (descPos.value()->y / 100) + ((descHitbox.value()->h / 100) / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, entityId);
}

int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager)
{
    float descLeft = (desc.vPos.x / 100) - ((desc.spriteData.dimension.x / 100) / 2);
    float descRight = (desc.vPos.x / 100) + ((desc.spriteData.dimension.x / 100) / 2);
    float descTop = (desc.vPos.y / 100) - ((desc.spriteData.dimension.y / 100) / 2);
    float descBottom = (desc.vPos.y / 100) + ((desc.spriteData.dimension.y / 100) / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, desc.uniqueID);
}