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

/**
 * @struct SpriteComponent
 * @brief A component that represents a sprite in the ECS (Entity Component System).
 *
 * This component holds a sprite, its type, and hitbox dimensions. It provides
 * functionality to initialize the sprite with a texture, position, scale, and
 * optional texture rectangle.
 *
 * @var sf::Sprite SpriteComponent::sprite
 * The SFML sprite object.
 *
 * @var AScenes::SpriteType SpriteComponent::type
 * The type of the sprite, defined by the AScenes namespace.
 *
 * @var int SpriteComponent::hitboxX
 * The width of the sprite's hitbox.
 *
 * @var int SpriteComponent::hitboxY
 * The height of the sprite's hitbox.
 *
 * @fn SpriteComponent::SpriteComponent(sf::Texture &texture, const float posX, float posY, const
 * sf::Vector2f &scale, AScenes::SpriteType typeNb, sf::IntRect rect = sf::IntRect(0, 0, 0, 0))
 * @brief Constructs a SpriteComponent with the given parameters.
 *
 * @param texture The texture to be used for the sprite.
 * @param posX The X position of the sprite.
 * @param posY The Y position of the sprite.
 * @param scale The scale of the sprite.
 * @param typeNb The type of the sprite.
 * @param rect The texture rectangle to be used for the sprite (default is an empty rectangle).
 */
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
        if (rect != sf::IntRect(0, 0, 0, 0))
            sprite.setTextureRect(rect);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        hitboxX = rect.width;
        hitboxY = rect.height;
    }
};
