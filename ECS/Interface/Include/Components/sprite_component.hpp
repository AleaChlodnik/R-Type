/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include <iostream>

#include "sprite_type.hpp"
#include <SFML/Graphics.hpp>
#include <string>

struct SpriteComponent {
    sf::Sprite sprite;
    SpriteType type;

    SpriteComponent(sf::Texture &texture, const float posX, float posY, const sf::Vector2f &scale,
        SpriteType typeNb, sf::IntRect rect = {0, 0, 0, 0})
    {
        type = typeNb;
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scale);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
        if (rect != sf::IntRect(0,0,0,0))
            sprite.setTextureRect(rect);
    }
};
