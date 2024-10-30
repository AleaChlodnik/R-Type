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

    void addEntity(EntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, sf::Vector2u windowSize)
    {
        float posX = windowSize.x * (entity.vPos.x / 100.0f);
        float posY = windowSize.y * (entity.vPos.y / 100.0f);
        float scaleX = (entity.ratio.x * windowSize.x) / entity.animationComponent.dimension.x;
        float scaleY = (entity.ratio.y * windowSize.y) / entity.animationComponent.dimension.y;
        std::cout << "entityId: " << entity.uniqueID << std::endl;
        std::cout << "spritePath: " << SpriteFactory(entity.spriteData.spritePath) << std::endl;
        std::cout << "entityRatio: " << entity.ratio.x << ", " << entity.ratio.y << std::endl;
        std::cout << "screen scale: " << scaleX << ", " << scaleY << std::endl;
        std::cout << "spriteData: " << entity.spriteData << std::endl;
        sf::Texture &texture =
            textureManager.getTexture(SpriteFactory(entity.spriteData.spritePath));
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

    void moveEntity(
        uint32_t id, vf2d newPos, ComponentManager &componentManager, sf::Vector2u windowSize)
    {
        auto spriteEntity = componentManager.getComponent<SpriteComponent>(id);
        if (spriteEntity) {
            float posX = windowSize.x * (newPos.x / 100.0f);
            float posY = windowSize.y * (newPos.y / 100.0f);
            spriteEntity.value()->sprite.setPosition(posX, posY);
        } else {
            std::cerr << "Entity not found, id: " << id << std::endl;
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
