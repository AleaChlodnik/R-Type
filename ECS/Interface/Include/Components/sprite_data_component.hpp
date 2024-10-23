/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "../sprite_path.hpp"
#include "../sprite_type.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>

template <typename T> struct Vector {
    T x;
    T y;
};

struct Rect {
    Vector<float> offSet;
    Vector<float> size;
};

struct SpriteDataComponent {
    SpritePath spritePath;
    uint32_t nbOfSprites;
    Vector<float> scale;
    Rect rects; // do not use this in the network because it is not fixed size
    SpriteType type;
};
