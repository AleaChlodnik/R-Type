/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** bind_component
*/

#pragma once

#include "a_scenes.hpp"
#include "i_scenes.hpp"
#include <functional>

struct BindComponent {
    bool isHovered = false;
    std::function<IScenes *(AScenes *, AScenes::Actions)> bind;

    BindComponent(std::function<IScenes *(AScenes *, AScenes::Actions)> bindFunction)
        : bind(bindFunction){};
};
