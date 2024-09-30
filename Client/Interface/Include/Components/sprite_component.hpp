/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <string>

struct SpriteComponent {
    sf::Sprite sprite;

    SpriteComponent(sf::Texture &texture, const PositionComponent &position)
    {
        sprite.setTexture(texture);
        sprite.setPosition(position.x, position.y);
    }
};
