/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** spriteData
*/

#pragma once

#include <cstdint>
#include <string>

/**
 * @enum SpritePath
 * @brief Enum class representing various sprite paths used in the game.
 *
 * This enum class defines a set of constants representing different sprite paths
 * that can be used in the game. Each constant corresponds to a specific sprite.
 *
 * @var SpritePath::Ship1
 * Represents the path for the first ship sprite.
 *
 * @var SpritePath::Ship2
 * Represents the path for the second ship sprite.
 *
 * @var SpritePath::Ship3
 * Represents the path for the third ship sprite.
 *
 * @var SpritePath::Ship4
 * Represents the path for the fourth ship sprite.
 *
 * @var SpritePath::Enemy1
 * Represents the path for the first enemy sprite.
 *
 * @var SpritePath::Enemy2
 * Represents the path for the second enemy sprite.
 *
 * @var SpritePath::Enemy3
 * Represents the path for the third enemy sprite.
 *
 * @var SpritePath::Enemy4
 * Represents the path for the fourth enemy sprite.
 *
 * @var SpritePath::Enemy5
 * Represents the path for the fifth enemy sprite.
 *
 * @var SpritePath::Enemy6
 * Represents the path for the sixth enemy sprite.
 *
 * @var SpritePath::Missile
 * Represents the path for the missile sprite.
 *
 * @var SpritePath::ForceWeapon
 * Represents the path for the force weapon sprite.
 *
 * @var SpritePath::ForceMissile
 * Represents the path for the force missile sprite.
 *
 * @var SpritePath::BlueLaserCrystal
 * Represents the path for the blue laser crystal sprite.
 *
 * @var SpritePath::Background1
 * Represents the path for the first background sprite.
 *
 * @var SpritePath::Background2
 * Represents the path for the second background sprite.
 *
 * @var SpritePath::Background3
 * Represents the path for the third background sprite.
 *
 * @var SpritePath::Explosion
 * Represents the path for the explosion sprite.
 *
 * @var SpritePath::PowerUp
 * Represents the path for the power-up sprite.
 *
 * @var SpritePath::Boss
 * Represents the path for the boss sprite.
 *
 * @var SpritePath::BossBullet
 * Represents the path for the boss bullet sprite.
 *
 * @var SpritePath::Bar
 * Represents the path for the bar sprite.
 *
 * @var SpritePath::Wall
 * Represents the path for the wall sprite.
 *
 * @var SpritePath::NONE
 * Represents an undefined or no sprite path.
 */
enum class SpritePath : uint32_t
{
    Ship1,
    Ship2,
    Ship3,
    Ship4,
    Enemy1,
    Enemy2,
    Enemy3,
    Enemy4,
    Enemy5,
    Enemy6,
    Missile,
    ForceWeapon,
    ForceMissile,
    BlueLaserCrystal,
    Background1,
    Background2,
    Background3,
    Explosion,
    PowerUp,
    Boss,
    BossBullet,
    Bar,
    Wall,
    NONE,
};

/**
 * @brief Factory function to get the string representation of a sprite path.
 *
 * This function takes a SpritePath enum value and returns the corresponding
 * string representation of the sprite path.
 *
 * @param sprite The SpritePath enum value.
 * @return std::string The string representation of the sprite path.
 */
std::string SpriteFactory(SpritePath sprite);

/**
 * @brief Overloaded output stream operator for SpritePath.
 *
 * This operator allows the SpritePath enum value to be output to an
 * output stream, such as std::cout.
 *
 * @param os The output stream.
 * @param spritePath The SpritePath enum value.
 * @return std::ostream& The output stream with the sprite path written to it.
 */
std::ostream &operator<<(std::ostream &os, const SpritePath &spritePath);
