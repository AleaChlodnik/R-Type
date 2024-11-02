/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** auto_fire_system
*/

#pragma once

#include "Systems/i_system.hpp"

/**
 * @class AutoFireSystem
 * @brief A system that handles automatic firing mechanisms for entities.
 *
 * The AutoFireSystem class is responsible for managing the automatic firing
 * behavior of entities within the ECS framework. It interacts with the
 * ComponentManager and EntityManager to update and control the firing state
 * of entities.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 */
class AutoFireSystem : public ISystem {
  public:
    /**
     * @class AutoFireSystem
     * @brief System responsible for handling automatic firing mechanisms in entities.
     *
     * @param componentManager Reference to the ComponentManager that manages all components.
     * @param entityManager Reference to the EntityManager that manages all entities.
     */
    AutoFireSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    /**
     * @brief Handles the automatic firing mechanism for entities.
     *
     * This function processes entities that have the auto-fire capability and
     * triggers their firing actions based on the game logic and conditions.
     *
     * @param componentManager Reference to the ComponentManager that manages all components.
     * @param entityManager Reference to the EntityManager that manages all entities.
     */
    void handleAutoFire(ComponentManager &componentManager, EntityManager &entityManager);

  private:
    /**
     * @brief Reference to the ComponentManager instance.
     *
     * This member variable holds a reference to the ComponentManager, which is responsible
     * for managing all the components within the ECS (Entity Component System). It is used
     * by the system to access and manipulate components associated with entities.
     */
    ComponentManager &_componentManager;
    /**
     * @brief Reference to the EntityManager instance.
     *
     * This member variable holds a reference to the EntityManager, which is responsible
     * for managing the entities within the ECS (Entity Component System). It is used
     * to perform operations such as adding, removing, and querying entities.
     */
    EntityManager &_entityManager;
};
