/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#include "Systems/update_system.hpp"

void UpdateSystem::updateSpritePositions(ComponentManager &componentManager, EntityManager &entityManager)
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
                        sprite.value()->sprite.setPosition(
                            pos.value()->x, pos.value()->y);
                    }
                }
            }
        }
    }
}

// void UpdateSystem::updateBackground(ComponentManager &componentManager, float deltaTime)
// {
//     // Menu background scroll - just Client
//     auto backgroundOpt = componentManager.getComponentMap<BackgroundComponent>();
//     if (backgroundOpt) {
//         int backgroundId = 0;
//         auto &backgroundMap = **backgroundOpt;
//         if (!backgroundMap.empty()) {
//             auto entityId = backgroundMap.begin()->first;
//             backgroundId = entityId;
//         }
//         auto spriteOpt = componentManager.getComponent<SpriteComponent>(backgroundId);
//         auto offsetOpt = componentManager.getComponent<OffsetComponent>(backgroundId);
//         auto velOpt = componentManager.getComponent<VelocityComponent>(backgroundId);
//         if (spriteOpt && offsetOpt && velOpt) {
//             offsetOpt.value()->offset += velOpt.value()->speed * deltaTime;
//             float textureWidth = spriteOpt.value()->sprite.getTexture()->getSize().x;
//             if (offsetOpt.value()->offset > (textureWidth * 0.15)) {
//                 offsetOpt.value()->offset = 0;
//             }
//             sf::IntRect textureRect = spriteOpt.value()->sprite.getTextureRect();
//             textureRect.left = static_cast<int>(offsetOpt.value()->offset);
//             spriteOpt.value()->sprite.setTextureRect(textureRect);
//             return;
//         }
//     }

    /////////////////////////////////////////////////////////////////////////////// TEMPORARY
//     const auto spritesOpt = componentManager.getComponentMap<SpriteComponent>();
//     if (spritesOpt) {
//         auto &sprites = **spritesOpt;
//         auto bgSpriteIt = sprites.find(1);
//         if (bgSpriteIt != sprites.end()) {
//             auto &spriteComponent = bgSpriteIt->second;
//             auto bgSprite = std::any_cast<SpriteComponent>(&spriteComponent);
//             if (bgSprite) {
//                 int offset = getGameBgOffset();
//                 offset += static_cast<int>(300 * deltaTime);
//                 float textureWidth =
//                     static_cast<float>(bgSprite->sprite.getTexture()->getSize().x);
//                 if (offset > (textureWidth * 0.15)) {
//                     offset = 0;
//                 }
//                 sf::IntRect textureRect = bgSprite->sprite.getTextureRect();
//                 textureRect.left = offset;
//                 bgSprite->sprite.setTextureRect(textureRect);
//                 setGameBgOffset(offset);
//             }
//         }
//     }
// }
//////////////////////////////////////////////////////////////////////////////

// Game background scroll - from Server

// client
// will save bg offset sent by server in accessible variable
// auto spritesOpt =
// auto &sprites = **spritesOpt
// auto bgSprite = sprites[backgroundId].second;
// float textureWidth = bgsprite.value()->sprite.getTexture()->getSize().x;
// if (offset sent by server is > (textureWidth * 0.35)) {
//     send message to server that offset is now 0,
//         and it continues and sends me the next started over after 0 offset afterwards set
//             offset value to 0;
// }
// sf::IntRect textureRect = bgsprite.value()->sprite.getTextureRect();
// textureRect.left = static_cast<int>(offset.value()->offset);
// bgsprite.value()->sprite.setTextureRect(textureRect);

// server
// will also keep background id in an accessible variable
// auto offset = bgId
// auto velocity = bgId
// deltaTime
// offsetOpt.value()->offset += velOpt.value()->speed * deltaTime;
// send float offset = offsetOpt.value()->offset; to client & await offset client sends back
// offsetOpt.value()->offset = offset that client sent;

// bool UpdateSystem::updatePlayerMissile(int entityId, EntityManager &entityManager,
//     ComponentManager &componentManager, float deltaTime)
// {
//     auto posOpt = componentManager.getComponent<PositionComponent>(entityId);
//     auto velOpt = componentManager.getComponent<VelocityComponent>(entityId);
//     auto spriteOpt = componentManager.getComponent<SpriteComponent>(entityId);
//     if (posOpt && velOpt && spriteOpt) {
//         posOpt.value()->x += velOpt.value()->speed * deltaTime;
//         spriteOpt.value()->sprite.setPosition(posOpt.value()->x, posOpt.value()->y);
//         if (posOpt.value()->x >= this->_window.getSize().x) {
//             return true;
//         }
//     }
//     return false;
// }
