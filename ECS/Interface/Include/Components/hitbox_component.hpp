/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** hitbox_component
*/

#pragma once

/**
 * @struct HitboxComponent
 * @brief Represents the hitbox dimensions of an entity.
 *
 * This component is used to define the width and height of an entity's hitbox
 * in the game. It is typically used for collision detection purposes.
 *
 * @var HitboxComponent::w
 * Width of the hitbox.
 *
 * @var HitboxComponent::h
 * Height of the hitbox.
 */
struct HitboxComponent {
    int w;
    int h;
};
