/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "Systems/i_system.hpp"

class UpdateSystem : public ISystem {
  public:
    UpdateSystem(
        sf::RenderWindow &window, ComponentManager &componentManager, EntityManager &entityManager)
        : _window(window), _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    void update(float deltaTime) override
    {
        updateSpritePositions(this->_componentManager, this->_entityManager);
    }

    void updateSpritePositions(ComponentManager &componentManager, EntityManager &entityManager);

  private:
    sf::RenderWindow &_window;
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
