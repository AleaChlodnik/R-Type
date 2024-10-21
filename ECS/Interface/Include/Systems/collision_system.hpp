/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#pragma once

#include "Systems/i_system.hpp"

class CollisionSystem : public ISystem {
  public:
    CollisionSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager) {}

    void update(float deltaTime) override { checkCollisions(); }

    void checkCollisions();

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
