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
        if (componentManager.getComponent<MissileComponent>(entityId)) {
            if (updateMissile(entityId, entityManager, componentManager, deltaTime))
                entitiesToRemove.push_back(entityId);
        }
    }
    for (const auto &entityId : entitiesToRemove) {
        entityManager.removeEntity(entityId);
    }
}

bool UpdateSystem::updateMissile(int entityId, EntityManager &entityManager, ComponentManager &componentManager, float deltaTime)
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

void UpdateSystem::updateBackground(int entityId, ComponentManager &componentManager, float deltaTime)
{
    auto offsetOpt = componentManager.getComponent<OffsetComponent>(entityId);
    auto velOpt = componentManager.getComponent<VelocityComponent>(entityId);
    if (offsetOpt && velOpt) {
        offsetOpt.value()->offset += velOpt.value()->speed * deltaTime;
        auto spriteOpt = componentManager.getComponent<SpriteComponent>(entityId);
        float textureWidth = spriteOpt.value()->sprite.getTexture()->getSize().x;
        if (offsetOpt.value()->offset >= textureWidth) {
            offsetOpt.value()->offset = 0;
        }
        spriteOpt.value()->sprite.setTextureRect(
            sf::IntRect(static_cast<int>(offsetOpt.value()->offset), 0,
                static_cast<int>(this->_window.getSize().x), static_cast<int>(this->_window.getSize().y)));
    }
}
