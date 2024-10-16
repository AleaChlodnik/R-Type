/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** bind_component
*/

#pragma once

#include "scenes.hpp"
#include <functional>

struct BindComponent {
    bool isHovered = false;
    std::function<Scenes *(Scenes *, Scenes::Actions)> bind;

    BindComponent(std::function<Scenes *(Scenes *, Scenes::Actions)> bindFunction) : bind(bindFunction){};
};
