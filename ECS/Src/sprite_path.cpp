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
        return "Client/Assets/Sprites/Ships/ship1.png";
    } break;
    case SpritePath::Ship2: {
        return "Client/Assets/Sprites/Ships/ship2.png";
    } break;
    case SpritePath::Ship3: {
        return "Client/Assets/Sprites/Ships/ship4.png";
    } break;
    case SpritePath::Ship4: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Enemy1: {
        return "Client/Assets/Sprites/Enemies/enemy1.png";
    } break;
    case SpritePath::Enemy2: {
        return "Client/Assets/Sprites/Enemies/enemy2.png";
    } break;
    case SpritePath::Enemy3: {
        return "Client/Assets/Sprites/Enemies/enemy3.png";
    } break;
    case SpritePath::Enemy4: {
        return "Client/Assets/Sprites/Enemies/enemy4.png";
    } break;
    case SpritePath::Enemy5: {
        return "Client/Assets/Sprites/Enemies/enemy5.png";
    } break;
    case SpritePath::Enemy6: {
        return "Client/Assets/Sprites/Enemies/enemy5.png";
    } break;
    case SpritePath::Monster1: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Monster2: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Monster3: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Monster4: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Monster5: {
        return "Client/Assets/Sprites/Ships/ship5.png";
    } break;
    case SpritePath::Missile: {
        return "Client/Assets/Sprites/Missiles/missile.png";
    } break;
    case SpritePath::Background: {
        return "Client/Assets/Sprites/Background/background.jpg";
    } break;
    default: {
        return "";
    } break;
    }
}
