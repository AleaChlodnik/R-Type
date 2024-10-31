/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** weapon_component
*/

#pragma once

struct WeaponComponent {
    float damage;
    float fire_rate;
    float bullet_speed;

    WeaponComponent(float _damage, float _fire_rate, float _bullet_speed)
        : damage(_damage), fire_rate(_fire_rate), bullet_speed(_bullet_speed)
    {
    }
};