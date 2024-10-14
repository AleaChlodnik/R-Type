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
    std::vector<int> entitiesToRemove;

    for (const auto &entity : entities) {
        int entityId = entity.getId();
        if (componentManager.getComponent<BackgroundComponent>(entityId)) {
            updateBackground(entityId, componentManager, deltaTime);
        }
        if (componentManager.getComponent<PlayerMissileComponent>(entityId)) {
            if (updatePlayerMissile(entityId, entityManager, componentManager, deltaTime))
                entitiesToRemove.push_back(entityId);
        }
    }
    for (const auto &entityId : entitiesToRemove) {
        entityManager.removeEntity(entityId);
    }
}

bool UpdateSystem::updatePlayerMissile(int entityId, EntityManager &entityManager,
    ComponentManager &componentManager, float deltaTime)
{
    auto posOpt = componentManager.getComponent<PositionComponent>(entityId);
    auto velOpt = componentManager.getComponent<VelocityComponent>(entityId);
    auto spriteOpt = componentManager.getComponent<SpriteComponent>(entityId);
    if (posOpt && velOpt && spriteOpt) {
        posOpt.value()->x += velOpt.value()->speed * deltaTime;
        spriteOpt.value()->sprite.setPosition(posOpt.value()->x, posOpt.value()->y);
        if (posOpt.value()->x >= this->_window.getSize().x) {
            return true;
        }
    }
    return false;
}

void UpdateSystem::updateBackground(
    int entityId, ComponentManager &componentManager, float deltaTime)
{
    auto spriteOpt = componentManager.getComponent<SpriteComponent>(entityId);
    auto offsetOpt = componentManager.getComponent<OffsetComponent>(entityId);
    auto velOpt = componentManager.getComponent<VelocityComponent>(entityId);
    if (spriteOpt && offsetOpt && velOpt) {
        offsetOpt.value()->offset += velOpt.value()->speed * deltaTime;
        float textureWidth = spriteOpt.value()->sprite.getTexture()->getSize().x;
        if (offsetOpt.value()->offset > (textureWidth * 0.35)) {
            offsetOpt.value()->offset = 0;
        }
        sf::IntRect textureRect = spriteOpt.value()->sprite.getTextureRect();
        textureRect.left = static_cast<int>(offsetOpt.value()->offset);
        spriteOpt.value()->sprite.setTextureRect(textureRect);
    }
}
