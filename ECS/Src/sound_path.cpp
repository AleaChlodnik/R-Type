/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sound_path
*/

#include <sound_path.hpp>

std::string SoundFactory(ActionType action)
{
    switch (action) {
    case ActionType::Win: {
        return "Client/Assets/Sounds/win.ogg";
    } break;
    case ActionType::Shot: {
        return "Client/Assets/Sounds/shot.ogg";
    } break;
    case ActionType::Boss: {
        return "Client/Assets/Sounds/boss.ogg";
    } break;
    case ActionType::PowerUp: {
        return "Client/Assets/Sounds/power_up.ogg";
    } break;
    case ActionType::GameOver: {
        return "Client/Assets/Sounds/game_over.ogg";
    } break;
    case ActionType::BossDeath: {
        return "Client/Assets/Sounds/boss_death.ogg";
    } break;
    case ActionType::Explosion: {
        return "Client/Assets/Sounds/explosion.ogg";
    } break;
    case ActionType::Background: {
        return "Client/Assets/Sounds/background.ogg";
    } break;
    default: {
        return "";
    } break;
    }
}
