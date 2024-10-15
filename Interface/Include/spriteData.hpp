/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** spriteData
*/

#pragma once

#include <cstdint>
#include <string>

template<typename T>
struct Vector {
    T x;
    T y;
};

typedef struct SpriteData_s {
    std::string spritePath;
    Vector<uint32_t> offSet;
    Vector<uint32_t> dimension;
    Vector<float> scale;
} SpriteData_t;

enum class SpriteType : uint32_t
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
    case SpriteType::Enemy1: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy1.png", 0, 0, 80, 160};
    } break;
    case SpriteType::Enemy2: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy2.png", 0, 0, 128, 88};
    } break;
    case SpriteType::Enemy3: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy3.png", 0, 0, 116, 136};
    } break;
    case SpriteType::Enemy4: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy4.png", 0, 0, 128, 144};
    } break;
    case SpriteType::Enemy5: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy5.png", 0, 0, 96, 136};
    } break;
    case SpriteType::Enemy6: {
        return SpriteData_t{"Client/Assets/Sprites/Enemies/enemy5.png", 0, 0, 144, 176};
    } break;
    case SpriteType::Monster1: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 104, 136, 272, 224};
    } break;
    case SpriteType::Monster2: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 88, 152, 304, 232};
    } break;
    case SpriteType::Monster3: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 0, 0, 0, 0};
    } break;
    case SpriteType::Monster4: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 0, 0, 0, 0};
    } break;
    case SpriteType::Monster5: {
        return SpriteData_t{"Client/Assets/Sprites/Ships/ship5.png", 0, 0, 0, 0};
    } break;
    default: {
        return SpriteData_t{"", 0, 0, 0, 0};
    } break;
    }
}
