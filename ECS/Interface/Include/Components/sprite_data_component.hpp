/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "../sprite_path.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>

template <typename T> struct Vector {
    T x;
    T y;
};

struct SpriteDataComponent {
    SpritePath spritePath;
    Vector<uint32_t> offSet;
    Vector<uint32_t> dimension;
    Vector<float> scale;
};
