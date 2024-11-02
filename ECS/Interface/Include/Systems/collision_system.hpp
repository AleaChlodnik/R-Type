/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_system
*/

#pragma once

#include "Systems/i_system.hpp"

class CollisionSystem : public ISystem {
  public:
    /**
     * @class CollisionSystem
     * @brief Manages collision detection and response within the ECS framework.
     *
     * This system is responsible for handling all collision-related logic,
     * including detecting collisions between entities and responding to them
     * appropriately.
     *
     * @param componentManager Reference to the ComponentManager that handles
     *                         the components of the entities.
     * @param entityManager Reference to the EntityManager that manages the
     *                      entities in the system.
     */
    CollisionSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager)
    {
    }

    /**
     * @brief Checks for a collision between two entities.
     *
     * This function determines whether there is a collision between the components
     * of two specified entities within the component manager.
     *
     * @param componentManager Reference to the ComponentManager that holds the components of all entities.
     * @param entityId1 The ID of the first entity to check for collision.
     * @param entityId2 The ID of the second entity to check for collision.
     * @return true if a collision is detected between the two entities, false otherwise.
     */
    bool checkCollision(ComponentManager &componentManager, int entityId1, int entityId2);

    /**
     * @brief Checks if the entity with the given ID is off the screen.
     *
     * This function determines whether the specified entity is outside the
     * visible screen area based on its components managed by the ComponentManager.
     *
     * @param componentManager Reference to the ComponentManager that manages the entity's components.
     * @param entityId The ID of the entity to check.
     * @return true if the entity is off the screen, false otherwise.
     */
    bool checkOffScreen(ComponentManager &componentManager, int entityId);

  private:
    /**
     * @brief Reference to the ComponentManager instance.
     *
     * This member is used to manage and access various components within the ECS (Entity Component System).
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
