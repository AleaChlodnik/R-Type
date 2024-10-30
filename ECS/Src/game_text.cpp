/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game_text
*/

#include <game_text.hpp>

std::string GameTextFactory(GameText text)
{
    switch (text) {
    case GameText::Lives:
        return "Lives:";
        break;
    case GameText::Score:
        return "Score:";
        break;
    default:
        return "";
        break;
    }
}
