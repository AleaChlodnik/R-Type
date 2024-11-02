/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** input_component
*/

#pragma once

/**
 * @enum InputType
 * @brief Enumeration of possible input actions.
 *
 * This enumeration defines the different types of inputs that can be handled by the
 * InputComponent.
 *
 * @var InputType::UP
 * Represents the "up" input action.
 *
 * @var InputType::DOWN
 * Represents the "down" input action.
 *
 * @var InputType::LEFT
 * Represents the "left" input action.
 *
 * @var InputType::RIGHT
 * Represents the "right" input action.
 *
 * @var InputType::SHOOT
 * Represents the "shoot" input action.
 *
 * @var InputType::QUIT
 * Represents the "quit" input action.
 *
 * @var InputType::NONE
 * Represents no input action.
 */
enum class InputType
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SHOOT,
    QUIT,
    NONE
};

/**
 * @struct InputComponent
 * @brief Component for handling input actions.
 *
 * This structure is used to store the current input action of an entity.
 *
 * @var InputComponent::input
 * The current input action of the entity.
 */
struct InputComponent {
    InputType input;
};