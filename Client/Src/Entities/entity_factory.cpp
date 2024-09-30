/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "entity_factory.hpp"
#include <SFML/Graphics.hpp>

Entity EntityFactory::createPlayer(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity player = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Player/r-typesheet1.gif");

    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position);

    componentManager.addComponent<PositionComponent>(player.getId(), start_position.x, start_position.y);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);

    return player;
}
