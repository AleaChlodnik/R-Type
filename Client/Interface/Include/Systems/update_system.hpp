/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Components/components.hpp"
#include "Entities/entity_manager.hpp"
#include "Systems/i_system.hpp"

class UpdateSystem : public ISystem {
  public:
    UpdateSystem(sf::RenderWindow &window) : _window(window) {}

    void update(EntityManager &entityManager, ComponentManager &componentManager, float deltaTime);

    void updateBackground(int entityId, ComponentManager &componentManager, float deltaTime);
    bool updateMissile(int entityId, EntityManager &entityManager, ComponentManager &componentManager, float deltaTime);

  private:
    sf::RenderWindow &_window;
};
