/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include "Systems/i_system.hpp"
#include <error_handling.hpp>

class RenderSystem : public ISystem {
  public:
    RenderSystem(sf::RenderWindow &window, ComponentManager &componentManager)
        : _window(window), _componentManager(componentManager)
    {
        if (!_font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF")) {
            throw failedToLoadFont();
        }
    }

    void render(ComponentManager &componentManager);

  private:
    sf::RenderWindow &_window;
    ComponentManager &_componentManager;
    sf::Font _font;
};
