/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include "Systems/i_system.hpp"
#include <SFML/Graphics.hpp>

/**
 * @class RenderSystem
 * @brief A system responsible for rendering components.
 */
class RenderSystem : public ISystem {
  public:
    /**
     * @brief Construct a new Render System object
     * @brief A system responsible for rendering entities on a given window.
     *
     * @param window
     *
     * This system takes a reference to an sf::RenderWindow object and is responsible for rendering
     * entities on that window. It provides functionality to render sprites, shapes, and other
     * graphical components associated with entities in the game.
     */
    RenderSystem(sf::RenderWindow &window) : _window(window) {}

    /**
     * @brief Renders the components managed by the given ComponentManager.
     *
     * @param componentManager The ComponentManager that manages the components to be rendered.
     *
     * This function is responsible for rendering the components managed by the provided
     * ComponentManager. It takes the ComponentManager as a parameter and performs the necessary
     * rendering operations.
     */
    void render(ComponentManager &componentManager);

  private:
    sf::RenderWindow &_window;
};
