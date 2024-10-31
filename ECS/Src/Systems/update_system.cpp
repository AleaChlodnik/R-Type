/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#include "Systems/update_system.hpp"

void UpdateSystem::updateSpritePositions(
    ComponentManager &componentManager, EntityManager &entityManager)
{
    const auto &entities = entityManager.getAllEntities();
    if (!entities.empty()) {
        for (const auto &entity : entities) {
            auto sprite = componentManager.getComponent<SpriteComponent>(entity.getId());
            if (sprite) {
                auto pos = componentManager.getComponent<PositionComponent>(entity.getId());
                if (pos) {
                    if (sprite.value()->sprite.getPosition().x != pos.value()->x ||
                        sprite.value()->sprite.getPosition().y != pos.value()->y) {
                        sprite.value()->sprite.setPosition(pos.value()->x, pos.value()->y);
                    }
                }
            }
        }
    }
}
