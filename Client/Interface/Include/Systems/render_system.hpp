/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Systems/i_system.hpp"

class RenderSystem : public ISystem {
  public:
    RenderSystem(sf::RenderWindow &window) : _window(window) {}

    void update(EntityManager &entityManager, ComponentManager &componentManager, float deltaTime) override;
    void render(EntityManager &entityManager, ComponentManager &componentManager) override;

  private:
    sf::RenderWindow &_window;
};
