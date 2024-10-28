/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#pragma once

#include "Systems/i_system.hpp"

class MoveSystem : public ISystem {
  public:
    MoveSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager){};

    void moveEntities(
        ComponentManager &componentManager, EntityManager &entityManager);

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
