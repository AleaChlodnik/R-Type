/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** spriteData
*/

#include <sprite_path.hpp>

std::string SpriteFactory(SpritePath sprite)
{
    switch (sprite) {
    case SpritePath::Ship1: {
        return "Client/Assets/Sprites/Ships/ship_sheet.gif";
    } break;
    case SpritePath::Ship2: {
        return "Client/Assets/Sprites/Ships/ship_sheet.gif";
    } break;
    case SpritePath::Ship3: {
        return "Client/Assets/Sprites/Ships/ship_sheet.gif";
    } break;
    case SpritePath::Ship4: {
        return "Client/Assets/Sprites/Ships/ship_sheet.gif";
    } break;
    case SpritePath::Enemy1: {
        return "Client/Assets/Sprites/Enemies/enemy_sheet1.gif";
    } break;
    case SpritePath::Enemy2: {
        return "Client/Assets/Sprites/Enemies/enemy_sheet2.gif";
    } break;
    case SpritePath::Enemy3: {
        return "Client/Assets/Sprites/Enemies/enemy_sheet3.gif";
    } break;
    case SpritePath::Missile: {
        return "Client/Assets/Sprites/Missiles/missile_sheet.gif";
    } break;
    case SpritePath::Background: {
        return "Client/Assets/Sprites/Background/background.jpg";
    } break;
    default: {
        return "";
    } break;
    }
}
