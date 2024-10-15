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
        TextureManager &textureManager)
    {
        sf::Texture &texture = componentManager.getTexture(entity.spriteData.spritePath);
        SpriteComponent sprite(texture, entity.vPos.x, entity.vPos.y, entity.spriteData.scale,
            entity.spriteData.offSet);
        componentManager.addComponent<SpriteComponent>(entity.uniqueID, sprite);
    }

    void removeEntity(int entityId, ComponentManager &componentManager)
    {
        componentManager.removeEntity<SpriteComponent>(entityId);
    }

    void updateEntity(EntityInformation entity, ComponentManager &componentManager)
    {
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto entitySprite = sprites[entity.uniqueID].second;
            auto spriteComponent = std::any_cast<SpriteComponent>(&entitySprite);
            SpriteComponent->sprite.setPosition(entity.vPos.x, entity.vPos.y);
        }
    }
};
} // namespace net
} // namespace r_type
