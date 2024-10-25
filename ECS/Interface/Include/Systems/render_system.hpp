/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include "Systems/i_system.hpp"

class RenderSystem : public ISystem {
  public:
    RenderSystem(sf::RenderWindow &window, ComponentManager &componentManager)
        : _window(window), _componentManager(componentManager)
    {
        if (!_font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF")) {
            std::cout << "Error loading font" << std::endl; ////////////////// Do proper error handling
        }
    }

    void update(float deltaTime) override { render(this->_componentManager); }

    void render(ComponentManager &componentManager);

  private:
    sf::RenderWindow &_window;
    ComponentManager &_componentManager;
    sf::Font _font;
};
