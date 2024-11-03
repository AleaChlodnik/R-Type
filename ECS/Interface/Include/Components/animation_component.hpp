/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** velocity_component
*/

#pragma once

#include <macros.hpp>

/**
 * @struct AnimationComponent
 * @brief A component that holds animation properties such as offset and dimension.
 *
 * This component is used to define the properties of an animation, including its offset and
 * dimension.
 *
 * @var AnimationComponent::offset
 * The offset of the animation.
 *
 * @var AnimationComponent::dimension
 * The dimension of the animation.
 *
 * @fn AnimationComponent::AnimationComponent(vf2d _offset, vf2d _dimension)
 * @brief Constructs an AnimationComponent with the given offset and dimension.
 *
 * @param _offset The offset of the animation.
 * @param _dimension The dimension of the animation.
 */
struct AnimationComponent {
    vf2d offset;
    vf2d dimension;

    AnimationComponent(vf2d _offset, vf2d _dimension) : offset(_offset), dimension(_dimension) {}
};

/**
 * @brief Inequality operator for AnimationComponent.
 *
 * This operator checks if two AnimationComponent instances are not equal.
 *
 * @param animation The first AnimationComponent instance.
 * @param other The second AnimationComponent instance.
 * @return true if the two AnimationComponent instances are not equal, false otherwise.
 */
bool operator!=(AnimationComponent animation, AnimationComponent other);
