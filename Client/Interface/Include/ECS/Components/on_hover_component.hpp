/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** on_hover_component
*/

#pragma once
#include <functional>

struct OnHoverComponent {
    bool isHovered = false;
    std::function<void()> onHover;

    OnHoverComponent(std::function<void()> onHoverFunction) : onHover(onHoverFunction){};
};
