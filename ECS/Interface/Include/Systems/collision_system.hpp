/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#pragma once

#include "Systems/i_system.hpp"
#include <Net/a_server.hpp>

class CollisionSystem : public ISystem {
  public:
    CollisionSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager) {}

    void update(float deltaTime) override { handleCollisions(this->_componentManager, this->_entityManager); }

    void handleCollisions(ComponentManager &componentManager, EntityManager &entityManager);

    bool checkCollision(ComponentManager &componentManager, int entityId1, int entityId2);

    void sendCollisionMessage(ComponentManager &componentManager, int entityId1, int entityId2);

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
