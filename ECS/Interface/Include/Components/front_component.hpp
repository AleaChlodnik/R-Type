/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ally_component
*/

#pragma once

#include <Entities/entity.hpp>
#include <memory>

/**
 * @brief A component that represents the front of an entity.
 *
 * This component is used to identify the target entity that this component is associated with.
 */
struct FrontComponent {
    int targetId;

    FrontComponent(int _targetId) : targetId(_targetId) {}
};
