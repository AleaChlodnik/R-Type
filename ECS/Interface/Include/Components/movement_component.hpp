/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** player_component
*/

#pragma once

#include <cstdint>

/**
 * @enum MovementType
 * @brief Enumeration of different types of movement behaviors.
 *
 * @var MovementType::WIGGLE
 * Represents a wiggling movement pattern.
 *
 * @var MovementType::DIAGONAL
 * Represents a diagonal movement pattern.
 *
 * @var MovementType::CIRCLE
 * Represents a circular movement pattern.
 */

enum class MovementType
{
    WIGGLE,
    DIAGONAL,
    CIRCLE
};

/**
 * @struct MovementComponent
 * @brief Component that defines the movement behavior of an entity.
 *
 * @var MovementComponent::movementType
 * The type of movement behavior.
 *
 * @var MovementComponent::index
 * An index value associated with the movement component.
 */
struct MovementComponent {
    MovementType movementType;
    uint32_t index;
};
