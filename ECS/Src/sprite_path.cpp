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
    case SpritePath::Background1: {
        return "Client/Assets/Sprites/Background/background1.png";
    } break;
    case SpritePath::Background2: {
        return "Client/Assets/Sprites/Background/background2.png";
    } break;
    case SpritePath::Background3: {
        return "Client/Assets/Sprites/Background/background5.png";
    } break;
    case SpritePath::ForceWeapon: {
        return "Client/Assets/Sprites/Weapon/weapon_sheet.gif";
    } break;
    case SpritePath::ForceMissile: {
        return "Client/Assets/Sprites/Weapon/weapon_sheet.gif";
    } break;
    case SpritePath::BlueLaserCrystal: {
        return "Client/Assets/Sprites/PowerUps/blue_laser_crystal.png";
    } break;
    case SpritePath::Bar: {
        return "Client/Assets/Sprites/Bars/info_bar.png";
    } break;
    case SpritePath::Wall: {
        return "Client/Assets/Sprites/Obstacles/wall.png";
    } break;
    case SpritePath::Boss: {
        return "Client/Assets/Sprites/Boss/boss_sheet.gif";
    } break;
    default: {
        return "";
    } break;
    }
}
