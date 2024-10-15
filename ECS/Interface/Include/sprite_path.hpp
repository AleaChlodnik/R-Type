/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** spriteData
*/

#pragma once

#include <cstdint>
#include <string>

enum class SpritePath : uint32_t
{
    Ship1,
    Ship2,
    Ship3,
    Ship4,
    Enemy1,
    Enemy2,
    Enemy3,
    Enemy4,
    Enemy5,
    Enemy6,
    Monster1,
    Monster2,
    Monster3,
    Monster4,
    Monster5,
    Missile,
    Background,
    Explosion,
    PowerUp,
    Boss,
    BossBullet,
    NONE,
};

std::string SpriteFactory(SpritePath sprite);
