/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "../sprite_path.hpp"
#include "animation_component.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <a_scenes.hpp>
#include <cstdint>
#include <macros.hpp>
#include <string>

/**
 * @struct SpriteDataComponent
 * @brief Component that holds data related to a sprite.
 *
 * This component contains information about the sprite's path, scale, and type.
 *
 * @var SpriteDataComponent::spritePath
 * Path to the sprite resource.
 *
 * @var SpriteDataComponent::scale
 * Scale factor for the sprite.
 *
 * @var SpriteDataComponent::type
 * Type of the sprite as defined in AScenes::SpriteType.
 */
struct SpriteDataComponent {
    SpritePath spritePath;
    vf2d scale;
    AScenes::SpriteType type;
};

/**
 * @brief Overloads the << operator to output the contents of a SpriteDataComponent to an ostream.
 *
 * @param os The output stream to which the SpriteDataComponent will be written.
 * @param spriteData The SpriteDataComponent instance to be written to the output stream.
 * @return std::ostream& The output stream after writing the SpriteDataComponent.
 */
std::ostream &operator<<(std::ostream &os, const SpriteDataComponent &spriteData);