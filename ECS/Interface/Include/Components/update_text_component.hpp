/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** on_click_component
*/

#pragma once
#include <a_scenes.hpp>
#include <functional>
#include <i_scenes.hpp>
#include <string>


struct UpdateTextComponent {
    std::function<std::string(GameParameters)> updateText;

    UpdateTextComponent(std::function<std::string(GameParameters)> updateTextFunction)
        : updateText(updateTextFunction){};
};