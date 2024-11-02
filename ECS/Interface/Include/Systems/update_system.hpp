/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "Systems/i_system.hpp"

/**
 * @class UpdateSystem
 * @brief A system responsible for updating sprite positions in the game.
 *
 * The UpdateSystem class inherits from the ISystem interface and is responsible
 * for updating the positions of sprites in the game. It interacts with the
 * ComponentManager and EntityManager to manage and update the components and entities.
 *
 * @param window Reference to the SFML RenderWindow object.
 * @param componentManager Reference to the ComponentManager object.
 * @param entityManager Reference to the EntityManager object.
 */
class UpdateSystem : public ISystem {
  public:
    /**
     * @brief Manages the update logic for entities within the ECS framework.
     *
     * @param window Reference to the SFML RenderWindow used for rendering.
     * @param componentManager Reference to the ComponentManager that handles components.
     * @param entityManager Reference to the EntityManager that handles entities.
     */
    UpdateSystem(
        sf::RenderWindow &window, ComponentManager &componentManager, EntityManager &entityManager)
        : _window(window), _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    /**
     * @brief Updates the positions of all sprite components in the game.
     *
     * This function iterates through all entities that have sprite components
     * and updates their positions based on their current velocities and other
     * relevant factors.
     *
     * @param componentManager Reference to the ComponentManager that manages all components.
     * @param entityManager Reference to the EntityManager that manages all entities.
     */
    void updateSpritePositions(ComponentManager &componentManager, EntityManager &entityManager);

  private:
    /**
     * @brief Reference to the SFML RenderWindow used for rendering.
     */
    sf::RenderWindow &_window;
    /**
     * @brief Reference to the ComponentManager instance.
     *
     * This member is used to manage and access various components within the ECS (Entity Component
     * System).
     */
    ComponentManager &_componentManager;
    /**
     * @brief Reference to the EntityManager instance.
     *
     * This member variable holds a reference to the EntityManager, which is responsible
     * for managing all entities within the ECS (Entity Component System). It provides
     * functionalities to create, destroy, and query entities.
     */
    EntityManager &_entityManager;
};
