/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include <error_handling.hpp>
#include <SFML/Graphics.hpp>
#include <string>

struct SpriteComponent {
    sf::Sprite sprite;

    SpriteComponent(
        sf::Texture &texture, const float posX, float posY, const sf::Vector2f &scale)
    {
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scale);
    }
};
