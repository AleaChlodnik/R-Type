/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** font_path
*/

#pragma once

#include <cstdint>
#include <string>

enum class FontPath : uint32_t
{
    MAIN,
    NONE
};

std::string FontFactory(FontPath font);

std::ostream &operator<<(std::ostream &os, const FontPath &fontPath);
