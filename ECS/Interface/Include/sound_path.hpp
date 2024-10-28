/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sound_path
*/

#pragma once

#include <cstdint>
#include <string>

enum class ActionType : uint32_t
{
    Win,
    Shot,
    Boss,
    PowerUp,
    GameOver,
    BossDeath,
    Explosion,
    Background,
    NONE,
};

std::string SoundFactory(ActionType action);

// std::ostream &operator<<(std::ostream &os, const ActionType &action);
