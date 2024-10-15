/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entities_struct
*/

#pragma once

#include <cstdint>
#include "Components/sprite_data_component.hpp"

struct vf2d {
    float x = 0;
    float y = 0;
};

struct EntityInformation {
    uint32_t uniqueID = 0;
    SpriteDataComponent spriteData;
    vf2d vPos;
};