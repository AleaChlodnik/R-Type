/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** player_component
*/

#pragma once

#include <cstdint>

enum class MovementType
{
    WIGGLE,
    DIAGONAL,
    CIRCLE
};

struct MovementComponent {
    MovementType movementType;
    uint32_t index;
};
