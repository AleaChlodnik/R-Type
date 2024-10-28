/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** auto_fire_system
*/

#pragma once

#include "Systems/i_system.hpp"

class AutoFireSystem : public ISystem {
  public:
    AutoFireSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    void handleAutoFire(ComponentManager &componentManager, EntityManager &entityManager);

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
