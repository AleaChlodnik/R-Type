/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Components/components.hpp"
#include "Entities/entity_manager.hpp"

class ISystem {
  public:
    ISystem() = default;
    virtual ~ISystem() = default;

    virtual void update(
        EntityManager &entityManager, ComponentManager &componentManager, float deltaTime) = 0;
    virtual void render(EntityManager &entityManager, ComponentManager &componentManager) = 0;
};
