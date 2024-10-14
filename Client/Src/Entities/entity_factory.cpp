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
    sf::Vector2f scale(1.0f, 1.0f);

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    VelocityComponent velocity(100.0f);
    OffsetComponent offset(0);
    SpriteComponent sprite(texture, start_position, scale);

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
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
        textureManager.getTexture("Client/Assets/Sprites/Player/Ship3/ship3.png");
    sf::Vector2f scale(1.3f, 1.3f);

    PlayerComponent playerComponent;
    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position, scale);

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), start_position);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);

    return player;
}

Entity EntityFactory::createMissile(int playerId, EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity missle = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missiles/missile.png");
    sf::Vector2f scale(0.1f, 0.1f);

    auto playerPosition = componentManager.getComponent<PositionComponent>(playerId);

    MissileComponent missileComponent;
    PositionComponent startPosition(
        playerPosition.value()->x + 105, playerPosition.value()->y + 49);
    VelocityComponent velocity(200.0f);
    SpriteComponent sprite(texture, startPosition, scale);

    componentManager.addComponent<MissileComponent>(missle.getId(), missileComponent);
    componentManager.addComponent<PositionComponent>(missle.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(missle.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(missle.getId(), sprite);

    return missle;
}

Entity EntityFactory::createButton(EntityManager &entityManager, ComponentManager &componentManager,
    TextureManager &textureManager, std::string text, std::function<Scenes *(Scenes *)> onClick)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position, scale);
    TextComponent textComponent(text);
    OnClickComponent onClickfunction(onClick);

    componentManager.addComponent<PositionComponent>(button.getId(), start_position);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);

    return button;
}