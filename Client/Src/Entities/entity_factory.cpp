/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include <SFML/Graphics.hpp>
#include "entity_factory.hpp"

Entity EntityFactory::createPlayer(EntityManager &entityManager, ComponentManager &componentManager)
{
    // Init entity
    Entity player = entityManager.createEntity();

    // Init all player components with all player values
    PositionComponent start_position(0, 0);
    SpriteComponent sprite("Client/Assets/Sprites/Player/r-typesheet1.gif",start_position);

    // Add components to player entity
    componentManager.addComponent<PositionComponent>(player.getId(), start_position.x, start_position.y);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);

    // Return entity: player
    return player;
}
