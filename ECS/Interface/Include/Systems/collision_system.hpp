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
        : _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    bool checkCollision(ComponentManager &componentManager, int entityId1, int entityId2);

    bool checkOffScreen(ComponentManager &componentManager, int entityId);

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
