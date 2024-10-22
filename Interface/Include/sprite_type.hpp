/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_type
*/

#pragma once

#include <cstdint>

/**
 * @enum SpriteType
 * @brief Enumeration representing the type of sprite in the game.
 *
 * This enumeration defines the different sprite types that need to be identified in the game.
 * The types include:
 * - BACKGROUND: Represents a background sprite.
 * - PLAYER: Represents a player sprite.
 * - ALLY: Represents an ally sprite.
 * - ENEMY: Represents an enemy sprite.
 * - OTHER: Represents any other type of sprite.
 */
enum class SpriteType : uint32_t
{
    BACKGROUND,
    PLAYER,
    ALLY,
    ENEMY,
    OTHER
};