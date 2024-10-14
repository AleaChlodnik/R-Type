/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite
*/

#pragma once

#include <cstdint>
#include <string>

typedef struct SpriteData_s {
    std::string spritePath;
    std::uint32_t offSetX;
    std::uint32_t offSetY;
    std::uint32_t height;
    std::uint32_t width;
} SpriteData_t;

enum class SpriteType : uint32_t
{
    Ship1,
    Ship2,
    Ship3,
    Ship4,
    Enemy,
    Bullet,
    Background,
    Explosion,
    PowerUp,
    Boss,
    BossBullet,
};

SpriteData_t Factory(SpriteType sprite)
{
    switch (sprite) {
    case SpriteType::Ship1: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship1.png", 16, 40, 96, 48};
    } break;
    case SpriteType::Ship2: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship2.png", 16, 40, 96, 48};
    } break;
    case SpriteType::Ship3: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship4.png", 16, 40, 96, 48};
    } break;
    case SpriteType::Ship4: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 16, 40, 96, 48};
    } break;
    default: {
        return SpriteData_t{"", 0, 0, 0, 0};
    } break;
    }
}
