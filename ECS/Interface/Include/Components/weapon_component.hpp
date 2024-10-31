/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** weapon_component
*/

#pragma once

#include <cstdint>

struct WeaponComponent {
    uint32_t playerId;
    uint32_t level;

    WeaponComponent(uint32_t _playerId, uint32_t _level) : playerId(_playerId), level(_level) {}
};