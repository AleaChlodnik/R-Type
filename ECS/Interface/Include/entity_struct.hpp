/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entities_struct
*/

#pragma once

#include "Components/sprite_data_component.hpp"
#include <cstdint>

/**
 * @struct vf2d
 * @brief Represents a 2D vector with x and y coordinates.
 * @var vf2d::x The x coordinate of the vector.
 * @var vf2d::y The y coordinate of the vector.
 */
struct vf2d {
    float x = 0;
    float y = 0;
};

/**
 * @struct EntityInformation
 * @brief Represents information about an entity.
 * @var EntityInformation::uniqueID The unique ID of the entity.
 * @var EntityInformation::spriteData The sprite data component of the entity.
 * @var EntityInformation::vPos The 2D vector representing the position of the entity.
 */
struct EntityInformation {
    uint32_t uniqueID = 0;
    SpriteDataComponent spriteData;
    vf2d vPos;
};
