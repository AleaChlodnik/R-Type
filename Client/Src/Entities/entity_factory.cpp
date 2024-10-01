/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Entities/entity_factory.hpp"
#include <SFML/Graphics.hpp>

Entity EntityFactory::createBackground(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity background = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");

    PositionComponent start_position(0, 0);
    VelocityComponent velocity(100.0f);
    OffsetComponent offset(0);
    SpriteComponent sprite(texture, start_position);

    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<VelocityComponent>(background.getId(), velocity);
    componentManager.addComponent<OffsetComponent>(background.getId(), offset);
    componentManager.addComponent<SpriteComponent>(background.getId(), sprite);

    return background;
}

Entity EntityFactory::createPlayer(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity player = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Player/r-typesheet1.gif");

    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position);

    componentManager.addComponent<PositionComponent>(player.getId(), start_position);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);

    return player;
}
