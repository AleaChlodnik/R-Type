/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "../sprite_path.hpp"
#include "animation_component.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <macros.hpp>
#include <string>
#include <a_scenes.hpp>

struct SpriteDataComponent {
    SpritePath spritePath;
    vf2d scale;
    AScenes::SpriteType type;
};

std::ostream &operator<<(std::ostream &os, const SpriteDataComponent &spriteData);