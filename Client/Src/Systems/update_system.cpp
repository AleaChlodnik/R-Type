/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#include "Systems/update_system.hpp"

void UpdateSystem::update(
    EntityManager &entityManager, ComponentManager &componentManager, float deltaTime)
{
    const auto &entities = entityManager.getAllEntities();

    for (const auto &entity : entities) {
        // update background
        auto offsetOpt = componentManager.getComponent<OffsetComponent>(entity.getId());
        auto velOpt = componentManager.getComponent<VelocityComponent>(entity.getId());
        if (offsetOpt && velOpt) {
            float updatedOffset = (offsetOpt.value()->offset += velOpt.value()->speed * deltaTime);
            componentManager.addComponent<OffsetComponent>(entity.getId(), updatedOffset);
            auto spriteOpt = componentManager.getComponent<SpriteComponent>(entity.getId());
            float textureWidth = spriteOpt.value()->sprite.getTexture()->getSize().x;
            if (offsetOpt.value()->offset >= textureWidth) {
                componentManager.addComponent<OffsetComponent>(entity.getId(), 0);
            }
            spriteOpt.value()->sprite.setTextureRect(
                sf::IntRect(static_cast<int>(offsetOpt.value()->offset), 0,
                    static_cast<int>(_window.getSize().x), static_cast<int>(_window.getSize().y)));
        }
    }
}
