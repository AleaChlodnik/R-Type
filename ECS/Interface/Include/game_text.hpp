/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game_text
*/

#pragma once

#include <cstdint>
#include <string>

enum class GameText : uint32_t {
    Lives,
    Score,
    NONE,
};

std::string GameTextFactory(GameText text);

std::ostream &operator<<(std::ostream &os, const GameText &text);
