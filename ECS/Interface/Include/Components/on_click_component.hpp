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

/**
 * @file on_click_component.hpp
 * @brief Defines the OnClickComponent structure used for handling click events in the ECS system.
 */

/**
 * @struct OnClickComponent
 * @brief Component that handles click events.
 *
 * This component is used to determine if an entity has been clicked and to execute a specified
 * function when the entity is clicked.
 *
 * @var OnClickComponent::isClicked
 * Indicates whether the entity has been clicked.
 *
 * @var OnClickComponent::onClick
 * A function that is executed when the entity is clicked. The function takes a pointer to an
 * AScenes object and returns a pointer to an IScenes object.
 *
 * @fn OnClickComponent::OnClickComponent(std::function<IScenes *(AScenes *)> onClickFunction)
 * @brief Constructs an OnClickComponent with the specified click handler function.
 *
 * @param onClickFunction The function to be executed when the entity is clicked.
 */
struct OnClickComponent {
    bool isClicked = false;
    std::function<IScenes *(AScenes *)> onClick;

    OnClickComponent(std::function<IScenes *(AScenes *)> onClickFunction)
        : onClick(onClickFunction){};
};