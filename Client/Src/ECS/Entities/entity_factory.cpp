/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Entities/entity_factory.hpp"
#include "Components/components.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>

Entity EntityFactory::createBackground(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    VelocityComponent velocity(200.0f);
    OffsetComponent offset(0);

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<VelocityComponent>(background.getId(), velocity);
    componentManager.addComponent<OffsetComponent>(background.getId(), offset);

    return background;
}

Entity EntityFactory::createButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<Scenes *(Scenes *)> onClick)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent start_position(0, 0);
    SpriteComponent sprite(texture, start_position.x, start_position.y, scale);
    TextComponent textComponent(text);
    OnClickComponent onClickfunction(onClick);

    componentManager.addComponent<PositionComponent>(button.getId(), start_position);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);

    return button;
}
