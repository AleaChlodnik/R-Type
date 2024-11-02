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
    /**
     * @class RenderSystem
     * @brief A system responsible for rendering entities in the ECS framework.
     *
     * This class handles the rendering of entities using the SFML library.
     * It requires a reference to an SFML RenderWindow and a ComponentManager.
     *
     * @param window Reference to the SFML RenderWindow where entities will be rendered.
     * @param componentManager Reference to the ComponentManager that manages entity components.
     *
     * @throws failedToLoadFont Exception thrown if the font file cannot be loaded.
     */
    RenderSystem(sf::RenderWindow &window, ComponentManager &componentManager)
        : _window(window), _componentManager(componentManager)
    {
        if (!_font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF")) {
            throw failedToLoadFont();
        }
    }

    /**
     * @brief Renders the components managed by the ComponentManager.
     *
     * This function iterates through the components in the provided ComponentManager
     * and performs rendering operations on them. It is typically called once per frame
     * to update the visual representation of the components.
     *
     * @param componentManager A reference to the ComponentManager that holds the components to be
     * rendered.
     */
    void render(ComponentManager &componentManager);

  private:
    /**
     * @brief Reference to the SFML RenderWindow used for rendering.
     */
    sf::RenderWindow &_window;
    /**
     * @brief Reference to the ComponentManager instance.
     *
     * This member variable holds a reference to the ComponentManager, which is responsible
     * for managing all the components within the ECS (Entity Component System). It provides
     * functionalities to add, remove, and access components associated with entities.
     */
    ComponentManager &_componentManager;
    /**
     * @brief A font object used for drawing text in SFML.
     *
     * This member variable holds an instance of sf::Font, which is used to load and manage font
     * resources for rendering text in the application. The sf::Font class provides functionality
     * to load fonts from files, memory, or streams, and to retrieve font metrics and glyphs for
     * text rendering.
     */
    sf::Font _font;
};
