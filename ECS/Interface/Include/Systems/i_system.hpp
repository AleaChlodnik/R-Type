/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Entities/entity_manager.hpp"
#include <SFML/Graphics.hpp>

/**
 * @class ISystem
 * @brief Interface for all systems in the ECS (Entity Component System) architecture.
 *
 * This class serves as a base class for all systems within the ECS framework.
 * Systems are responsible for processing entities that possess a specific set of components.
 *
 * @note This is an abstract class and should not be instantiated directly.
 */
class ISystem {
  public:
    ISystem() = default;
    virtual ~ISystem() = default;
};
