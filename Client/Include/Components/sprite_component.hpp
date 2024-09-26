/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "error_handling.hpp"

struct SpriteComponent {
    sf::Sprite sprite;
    sf::Texture texture;

    SpriteComponent(const std::string &filePath, const PositionComponent &position)
    {
        if (!texture.loadFromFile(filePath))
            throw failedToLoadTexture();

        sprite.setTexture(texture);
        sprite.setPosition(position.x, position.y);
    }
};
