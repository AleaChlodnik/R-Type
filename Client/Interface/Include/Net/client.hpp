/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#pragma once

#include <Net/a_client.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace r_type {
namespace net {
class Client : virtual public r_type::net::AClient<TypeMessage> {
  public:
    /**
     * @brief Send a message to the server to get the ping
     *
     */
    void PingServer()
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    /**
     * @brief Send a message to the server to all other clients
     *
     */
    void MessageAll()
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::MessageAll;
        Send(msg);
    }

    void initInfoBar(UIEntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, sf::Vector2u windowSize)
    {
        float windowWidth = static_cast<float>(windowSize.x);
        float windowHeight = static_cast<float>(windowSize.y);
        sf::Texture &texture =
            textureManager.getTexture(SpriteFactory(entity.spriteData.spritePath));
        sf::Vector2f scale(1.0f, 1.0f);
        SpriteComponent spriteComponent(texture, 0, 0, scale, entity.spriteData.type);
        componentManager.addComponent<SpriteComponent>(entity.uniqueID, spriteComponent);
        if (auto spriteEntity = componentManager.getComponent<SpriteComponent>(entity.uniqueID)) {
            float spriteWidth = spriteEntity.value()->sprite.getLocalBounds().width;
            float horizontalScale = windowWidth / spriteWidth;
            spriteEntity.value()->sprite.setScale(horizontalScale, 1.0f);
            spriteEntity.value()->sprite.setPosition(
                0, windowHeight - spriteEntity.value()->sprite.getGlobalBounds().height);

            sf::Font &font = fontManager.getFont(FontFactory(entity.textData.fontPath));
            float spriteHeight = spriteEntity.value()->sprite.getGlobalBounds().height;
            std::cout << "entity.textData.categorySize: " << entity.textData.categorySize << std::endl; /////////////////
            for (size_t i = 0; i < entity.textData.categorySize; i++) {
                // std::cout << "i: " << i << std::endl; ////////////////////////////////////////////////////////////////
                std::string displayText = GameTextFactory(entity.textData.categoryTexts[i]);
                float posX = 0.0f;
                float posY = (windowHeight - spriteHeight / 2.0f);
                if (entity.textData.categoryTexts[i] == GameText::Lives) {
                    posX = 10.0f;
                    displayText += std::to_string(entity.lives);
                } else if (entity.textData.categoryTexts[i] == GameText::Score) {
                    posX = windowWidth - 150.0f;
                    displayText += std::to_string(entity.score);
                }
                TextComponent textComponent(font, displayText, posX, posY);
                componentManager.addComponent<TextComponent>(entity.textData.categoryIds[i], textComponent);
            }
        }
    }

    void updateInfoBar(UIEntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager)
    {
        for (size_t i = 0; i < entity.textData.categorySize; i++) {
            if (auto textComponent = componentManager.getComponent<TextComponent>(entity.textData.categoryIds[i])) {
                std::string displayText = GameTextFactory(entity.textData.categoryTexts[i]);
                if (entity.textData.categoryTexts[i] == GameText::Lives) {
                    displayText += std::to_string(entity.lives);
                } else if (entity.textData.categoryTexts[i] == GameText::Score) {
                    displayText += std::to_string(entity.score);
                }
                textComponent.value()->text.setString(displayText);
            }
        }
    }

    void addEntity(EntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, sf::Vector2u windowSize)
    {
        if (entity.spriteData.type == AScenes::SpriteType::UI) {
            return;
        }
        float posX = windowSize.x * (entity.vPos.x / 100.0f);
        float posY = windowSize.y * (entity.vPos.y / 100.0f);
        float scaleX, scaleY;
        // std::cout << "posX: " << posX << " posY: " << posY << std::endl;
        // std::cout << "entityId: " << entity.uniqueID << std::endl;
        // std::cout << "spritePath: " << SpriteFactory(entity.spriteData.spritePath) << std::endl;
        // std::cout << "spriteData: " << entity.spriteData << std::endl;
        sf::Texture &texture =
            textureManager.getTexture(SpriteFactory(entity.spriteData.spritePath));
        scaleX = (entity.ratio.x * windowSize.x) / entity.animationComponent.dimension.x;
        scaleY = (entity.ratio.y * windowSize.y) / entity.animationComponent.dimension.y;
        // std::cout << "scaleX: " << scaleX << " scaleY: " << scaleY
        //           << " windowSize.x: " << windowSize.x << " windowSize.y: " << windowSize.y
        //           << " entity.animationComponent.dimension.x: "
        //           << entity.animationComponent.dimension.x
        //           << " entity.animationComponent.dimension.y: "
        //           << entity.animationComponent.dimension.y << std::endl;
        sf::Vector2f scale(scaleX, scaleY);
        sf::IntRect rect(entity.animationComponent.offset.x, entity.animationComponent.offset.y,
            entity.animationComponent.dimension.x, entity.animationComponent.dimension.y);
        SpriteComponent sprite(texture, posX, posY, scale, entity.spriteData.type, rect);
        componentManager.addComponent<SpriteComponent>(entity.uniqueID, sprite);
    }

    void removeEntity(int entityId, ComponentManager &componentManager)
    {
        componentManager.removeEntityFromComponent<SpriteComponent>(entityId);
    }

    void moveEntity(EntityInformation entity, ComponentManager &componentManager,
        sf::Vector2u windowSize, TextureManager &textureManager)
    {
        auto spriteEntity = componentManager.getComponent<SpriteComponent>(entity.uniqueID);
        if (spriteEntity) {
            float posX = windowSize.x * (entity.vPos.x / 100.0f);
            float posY = windowSize.y * (entity.vPos.y / 100.0f);
            spriteEntity.value()->sprite.setPosition(posX, posY);
        } else {
            addEntity(entity, componentManager, textureManager, windowSize);
        }
    }

    void animateEntity(int entityId, AnimationComponent rect, ComponentManager &componentManager)
    {
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto entitySpriteIt = sprites.find(entityId);
            if (entitySpriteIt != sprites.end()) {
                auto &spriteComponent = entitySpriteIt->second;
                if (auto entitySprite = std::any_cast<SpriteComponent>(&spriteComponent)) {
                    auto pos = componentManager.getComponent<PositionComponent>(entityId);
                    std::cout << "Animating entity " << entityId << " with new rect: "
                              << "offset(" << rect.offset.x << ", " << rect.offset.y << "), "
                              << "dimension(" << rect.dimension.x << ", " << rect.dimension.y
                              << ")" << std::endl;
                    if (pos)
                        std::cout << "position: " << pos.value()->x << ", " << pos.value()->y
                                  << std::endl;
                    sf::IntRect newRect(
                        rect.offset.x, rect.offset.y, rect.dimension.x, rect.dimension.y);
                    entitySprite->sprite.setTextureRect(newRect);
                }
            }
        }
    }
};
} // namespace net
} // namespace r_type
