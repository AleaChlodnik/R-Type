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
        return "Client/Assets/Sounds/win.wav";
    } break;
    case ActionType::Shot: {
        return "Client/Assets/Sounds/shot.wav";
    } break;
    case ActionType::Boss: {
        return "Client/Assets/Sounds/boss.wav";
    } break;
    case ActionType::PowerUp: {
        return "Client/Assets/Sounds/power_up.wav";
    } break;
    case ActionType::GameOver: {
        return "Client/Assets/Sounds/game_over.wav";
    } break;
    case ActionType::BossDeath: {
        return "Client/Assets/Sounds/boss_death.wav";
    } break;
    case ActionType::Explosion: {
        return "Client/Assets/Sounds/explosion.wav";
    } break;
    case ActionType::Background: {
        return "Client/Assets/Sounds/background.wav";
    } break;
    default: {
        return "";
    } break;
    }
}
