/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** weapon_component
*/

#pragma once

#include <cstdint>

struct ForceWeaponComponent {
    uint32_t playerId;
    uint32_t level;
    bool attached;

    ForceWeaponComponent(uint32_t _playerId, uint32_t _level, uint32_t _attached)
        : playerId(_playerId), level(_level), attached(_attached)
    {
    }
};