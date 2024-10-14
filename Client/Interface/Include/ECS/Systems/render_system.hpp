/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include "ECS/Systems/i_system.hpp"
#include <SFML/Graphics.hpp>

class RenderSystem : public ISystem {
  public:
    RenderSystem(sf::RenderWindow &window) : _window(window) {}

    void render(ComponentManager &componentManager);

  private:
    sf::RenderWindow &_window;
};
