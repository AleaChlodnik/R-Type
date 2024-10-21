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

                playerLeft = playerPos.value().x - (playerHitbox.value().w / 2);
                playerRight = playerPos.value().x + (playerHitbox.value().w / 2);
                playerTop = playerPos.value().y - (playerHitbox.value().h / 2);
                playerBottom = playerPos.value().y + (playerHitbox.value().h / 2);

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

    float descLeft = descPos.value().x - (descHitbox.value().w / 2);
    float descRight = descPos.value().x + (descHitbox.value().w / 2);
    float descTop = descPos.value().y - (descHitbox.value().h / 2);
    float descBottom = descPos.value().y + (descHitbox.value().h / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, entityId);
}

int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager)
{
    float descLeft = desc.vPos.x - (desc.spriteData.dimension.x / 2);
    float descRight = desc.vPos.x + (desc.spriteData.dimension.x / 2);
    float descTop = desc.vPos.y - (desc.spriteData.dimension.y / 2);
    float descBottom = desc.vPos.y + (desc.spriteData.dimension.y / 2);

    return CheckCollisionLogic(
        descLeft, descRight, descTop, descBottom, componentManager, entityManager, desc.uniqueID);
}