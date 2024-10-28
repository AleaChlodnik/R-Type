/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** velocity_component
*/

#pragma once

#include <macros.hpp>

struct AnimationComponent {
    vf2d offset;
    vf2d dimension;

    AnimationComponent(vf2d _offset, vf2d _dimension) : offset(_offset), dimension(_dimension) {}
};

bool operator!=(AnimationComponent animation, AnimationComponent other);