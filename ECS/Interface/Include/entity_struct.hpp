/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entities_struct
*/

#pragma once

#include "Components/sprite_data_component.hpp"
#include "Components/text_data_component.hpp"
#include <cstdint>
#include <macros.hpp>

/**
 * @struct EntityInformation
 * @brief Represents information about an entity.
 * @var EntityInformation::uniqueID The unique ID of the entity.
 * @var EntityInformation::spriteData The sprite data component of the entity.
 * @var EntityInformation::vPos The 2D vector representing the position of the entity.
 */
struct EntityInformation {
    uint32_t uniqueID = 0;
    vf2d ratio = {0, 0};
    SpriteDataComponent spriteData;
    vf2d vPos = {0, 0};
    AnimationComponent animationComponent = {{0, 0}, {0, 0}};
};

/**
 * @struct UIEntityInformation
 * @brief Represents the information of a UI entity in the game.
 *
 * This structure holds various attributes related to a UI entity,
 * including its unique identifier, lives, score, and associated
 * sprite and text data components.
 *
 * @var uint32_t UIEntityInformation::uniqueID
 * Unique identifier for the UI entity.
 *
 * @var uint32_t UIEntityInformation::lives
 * Number of lives the UI entity has.
 *
 * @var uint32_t UIEntityInformation::score
 * Score associated with the UI entity.
 *
 * @var SpriteDataComponent UIEntityInformation::spriteData
 * Data related to the sprite of the UI entity.
 *
 * @var TextDataComponent UIEntityInformation::textData
 * Data related to the text of the UI entity.
 */
struct UIEntityInformation {
    uint32_t uniqueID = 0;
    uint32_t lives = 0;
    uint32_t score = 0;
    SpriteDataComponent spriteData;
    TextDataComponent textData;
};
