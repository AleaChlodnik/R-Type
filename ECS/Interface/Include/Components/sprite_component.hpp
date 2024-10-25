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
        int typeNb, int dimensionX = 0, int dimensionY = 0)
    {
        type = static_cast<AScenes::SpriteType>(typeNb);
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scale);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        hitboxX = dimensionX;
        hitboxY = dimensionY;
    }
};
