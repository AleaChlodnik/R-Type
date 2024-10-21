/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** on_click_component
*/

#pragma once
#include <functional>
#include <i_scenes.hpp>
#include <a_scenes.hpp>

struct OnClickComponent {
    bool isClicked = false;
    std::function<IScenes *(AScenes *)> &onClick;

    OnClickComponent(std::function<IScenes *(AScenes *)> &onClickfunction)
        : onClick(onClickfunction){};
};