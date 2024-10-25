/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** shoot_component
*/

#pragma once

#include <chrono>

struct ShootComponent {
    std::chrono::system_clock::time_point nextShootTime;
    std::chrono::milliseconds cooldownTime;
    bool canShoot;

    ShootComponent(std::chrono::milliseconds cooldown)
        : nextShootTime(std::chrono::system_clock::now()), cooldownTime(cooldown)
    {
    }
};
