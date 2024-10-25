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

    SpriteComponent(
        sf::Texture &texture, const float posX, float posY, const sf::Vector2f &scale, int typeNb, sf::IntRect rect = sf::IntRect(0, 0, 0, 0))
    {
        type = static_cast<AScenes::SpriteType>(typeNb);
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(scale);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        if (rect != sf::IntRect(0, 0, 0, 0))
            sprite.setTextureRect(rect);
    }
};
