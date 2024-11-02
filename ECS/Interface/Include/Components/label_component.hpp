/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** label_component
*/

#pragma once

#include <string>

/**
 * @struct labelComponent
 * @brief Represents a label component with a name and position coordinates.
 *
 * This structure is used to define a label component in the ECS (Entity Component System).
 * It contains a name and the x and y coordinates for positioning.
 *
 * @var labelComponent::name
 * The name of the label.
 *
 * @var labelComponent::x
 * The x-coordinate of the label's position.
 *
 * @var labelComponent::y
 * The y-coordinate of the label's position.
 */
struct labelComponent {
    std::string name;
    int x;
    int y;
};
