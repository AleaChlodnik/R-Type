/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** velocity_component
*/

#pragma once

/**
 * @struct VelocityComponent
 * @brief Represents the velocity of an entity in 2D space.
 *
 * This component stores the velocity of an entity along the x and y axes.
 * It can be used to update the position of the entity based on its speed and direction.
 *
 * @var VelocityComponent::x
 * The velocity along the x-axis.
 *
 * @var VelocityComponent::y
 * The velocity along the y-axis.
 */
struct VelocityComponent {
    float x;
    float y;
};
