/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "ECS/Components/component_manager.hpp"
#include "ECS/Components/components.hpp"
#include "ECS/Systems/i_system.hpp"

class UpdateSystem : public ISystem {
  public:
    UpdateSystem(sf::RenderWindow &window) : _window(window) {}

    void update(EntityManager &entityManager, ComponentManager &componentManager, float deltaTime);

    void updateBackground(int entityId, ComponentManager &componentManager, float deltaTime);
    bool updatePlayerMissile(int entityId, EntityManager &entityManager,
        ComponentManager &componentManager, float deltaTime);

  private:
    sf::RenderWindow &_window;
};
