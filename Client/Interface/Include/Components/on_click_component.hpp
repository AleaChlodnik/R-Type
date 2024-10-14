/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** on_click_component
*/

#pragma once
#include <functional>
#include <scenes.hpp>

struct OnClickComponent {
    bool isClicked = false;
    std::function<Scenes *(Scenes *)> &onClick;

    OnClickComponent(std::function<Scenes *(Scenes *)> &onClickfunction) : onClick(onClickfunction) {};
};