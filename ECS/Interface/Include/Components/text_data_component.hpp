/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** text_data_component
*/

#pragma once

#include "../font_path.hpp"
#include "../game_text.hpp"

struct TextDataComponent {
    FontPath fontPath;
    uint32_t categoryIds[5] = {0};
    GameText categoryTexts[5];
    uint32_t categorySize = 0;
};
