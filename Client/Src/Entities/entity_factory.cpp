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

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Player/Ship3/ship3.png");

    PlayerComponent playerComponent;
    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position);

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), start_position);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);

    return player;
}

Entity EntityFactory::createMissle(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity missle = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missles/missle.png");

    
    PositionComponent startPosition(0, 0);
    auto entities = entityManager.getAllEntities();
    for (auto &entity : entities) {
        auto playerOpt = componentManager.getComponent<PlayerComponent>(entity.getId());
        if (playerOpt) {
            auto playerPosition = componentManager.getComponent<PositionComponent>(entity.getId());
            if (playerPosition)
                startPosition = *playerPosition.value();
        }
    }

    componentManager.addComponent<PositionComponent>(missle.getId(), startPosition);

    VelocityComponent velocity(1000.0f);
    SpriteComponent sprite(texture, startPosition);

    componentManager.addComponent<VelocityComponent>(missle.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(missle.getId(), sprite);

    return missle;
}
