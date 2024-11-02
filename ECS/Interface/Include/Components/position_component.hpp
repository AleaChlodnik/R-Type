/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** position_component
*/

#pragma once

/**
 * @brief A component that represents the position of an entity in 2D space.
 */
struct PositionComponent {
    float x;
    float y;

    PositionComponent(float _x, float _y) : x(_x), y(_y) {}
};
