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

/**
 * @struct BindComponent
 * @brief A component that binds a function to handle scene transitions.
 *
 * This component contains a function that takes two scene pointers and an action,
 * and returns a pointer to a new scene. It also has a flag to indicate if the component
 * is currently hovered.
 *
 * @var BindComponent::isHovered
 * A boolean flag indicating whether the component is currently hovered.
 *
 * @var BindComponent::bind
 * A std::function that takes two AScenes pointers and an AScenes::Actions, and returns a pointer to an IScenes.
 *
 * @fn BindComponent::BindComponent(std::function<IScenes *(AScenes *, AScenes::Actions)> bindFunction)
 * @brief Constructs a BindComponent with the given bind function.
 *
 * @param bindFunction The function to bind for handling scene transitions.
 */
struct BindComponent {
    bool isHovered = false;
    std::function<IScenes *(AScenes *, AScenes::Actions)> bind;

    BindComponent(std::function<IScenes *(AScenes *, AScenes::Actions)> bindFunction)
        : bind(bindFunction){};
};
