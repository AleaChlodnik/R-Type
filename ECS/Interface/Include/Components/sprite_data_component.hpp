/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/

#pragma once

#include "../error_handling.hpp"
#include "position_component.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>

template <typename T> struct Vector {
    T x;
    T y;
};

// enum class SpriteType : uint32_t
// {
//     Ship1,
//     Ship2,
//     Ship3,
//     Ship4,
//     Enemy1,
//     Enemy2,
//     Enemy3,
//     Enemy4,
//     Enemy5,
//     Enemy6,
//     Monster1,
//     Monster2,
//     Monster3,
//     Monster4,
//     Monster5,
//     Missle,
//     Background,
//     Explosion,
//     PowerUp,
//     Boss,
//     BossBullet,
//     NONE,
// };

struct SpriteDataComponent {
    std::string spritePath;
    Vector<uint32_t> offSet;
    Vector<uint32_t> dimension;
    Vector<float> scale;
};

// SpriteDataComponent SpriteFactory(SpriteType sprite)
// {
//     switch (sprite) {
//     case SpriteType::Ship1: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship1.png", {16, 40}, {96, 48}, {0,
//         0}};
//     } break;
//     case SpriteType::Ship2: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship2.png", {16, 40}, {96, 48}, {0,
//         0}};
//     } break;
//     case SpriteType::Ship3: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship3.png", {16, 40}, {96, 48}, {0,
//         0}};
//     } break;
//     case SpriteType::Ship4: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship4.png", {16, 40}, {96, 48}, {0,
//         0}};
//     } break;
//     case SpriteType::Enemy1: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Enemies/enemy1.png", {0, 0}, {80, 160}, {0,
//         0}};
//     } break;
//     case SpriteType::Enemy2: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Enemies/enemy2.png", {0, 0}, {128, 88}, {0,
//         0}};
//     } break;
//     case SpriteType::Enemy3: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Enemies/enemy3.png", {0, 0}, {116, 136}, {0, 0}};
//     } break;
//     case SpriteType::Enemy4: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Enemies/enemy4.png", {0, 0}, {128, 144}, {0, 0}};
//     } break;
//     case SpriteType::Enemy5: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Enemies/enemy5.png", {0, 0}, {96, 136}, {0,
//         0}};
//     } break;
//     case SpriteType::Enemy6: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Enemies/enemy5.png", {0, 0}, {144, 176}, {0, 0}};
//     } break;
//     case SpriteType::Monster1: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Ships/ship5.png", {104, 136}, {272, 224}, {0, 0}};
//     } break;
//     case SpriteType::Monster2: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Ships/ship5.png", {88, 152}, {304, 232}, {0, 0}};
//     } break;
//     case SpriteType::Monster3: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship5.png", {0, 0}, {0, 0}, {0, 0}};
//     } break;
//     case SpriteType::Monster4: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship5.png", {0, 0}, {0, 0}, {0, 0}};
//     } break;
//     case SpriteType::Monster5: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Ships/ship5.png", {0, 0}, {0, 0}, {0, 0}};
//     } break;
//     case SpriteType::Missle: {
//         return SpriteDataComponent{"Client/Assets/Sprites/Missiles/missile.png", {0, 0}, {16, 16}, {0,
//         0}};
//     } break;
//     case SpriteType::Background: {
//         return SpriteDataComponent{
//             "Client/Assets/Sprites/Background/background.jpg", {0, 0}, {0, 0}, {0, 0}};
//     } break;
//     default: {
//         return SpriteDataComponent{"", {0, 0}, {0, 0}, {0, 0}};
//     } break;
//     }
// }
