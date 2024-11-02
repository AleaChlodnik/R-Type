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
    CIRCLE,
    STRAIGHT
};

/**
 * @struct MovementComponent
 * @brief Represents a component that handles movement in the ECS system.
 *
 * This component is used to define the movement behavior of an entity.
 *
 * @var MovementComponent::movementType
 * The type of movement to be applied.
 *
 * @var MovementComponent::index
 * An index used to identify the movement component.
 *
 * @var MovementComponent::move
 * A boolean flag indicating whether the entity should move.
 *
 * @fn MovementComponent::MovementComponent(MovementType movementType, uint32_t index, bool move)
 * @brief Constructs a MovementComponent with the specified parameters.
 *
 * @param movementType The type of movement to be applied.
 * @param index An index used to identify the movement component.
 * @param move A boolean flag indicating whether the entity should move.
 */
struct MovementComponent {
    MovementType movementType;
    uint32_t index;
    bool move;

    MovementComponent()
        : movementType(MovementType::STRAIGHT), index(0), move(true)
    {
    }
    MovementComponent(MovementType movementType, uint32_t index, bool move)
        : movementType(movementType), index(index), move(move)
    {
    }
};
