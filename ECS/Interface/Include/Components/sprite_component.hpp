/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "a_scenes.hpp"
#include <SFML/Graphics.hpp>
#include <string>

struct SpriteComponent {
    sf::Sprite sprite;
    AScenes::SpriteType type;
    int hitboxX;
    int hitboxY;

    SpriteComponent(sf::Texture &texture, const float posX, float posY, const sf::Vector2f &scale,
        AScenes::SpriteType typeNb, sf::IntRect rect = sf::IntRect(0, 0, 0, 0))
    {
        type = typeNb;
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scale);
        if (type != AScenes::SpriteType::BACKGROUND)
            sprite.setOrigin(
                sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        if (rect != sf::IntRect(0, 0, 0, 0))
            sprite.setTextureRect(rect);
        hitboxX = rect.width;
        hitboxY = rect.height;
    }
};
