/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#pragma once

#include "i_system.hpp"

/**
 * @class MoveSystem
 * @brief System responsible for moving entities within the ECS framework.
 *
 * The MoveSystem class handles the movement logic for entities in the game.
 * It interacts with the ComponentManager and EntityManager to update the positions
 * of entities based on their movement components.
 */
class MoveSystem : public ISystem {
  public:
    /**
     * @brief Constructs a new MoveSystem object.
     *
     * @param componentManager Reference to the ComponentManager.
     * @param entityManager Reference to the EntityManager.
     */
    MoveSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager) {};
    /**
     * @brief Moves all entities managed by the system.
     *
     * This function iterates through all entities and updates their positions
     * based on their movement components.
     *
     * @param componentManager Reference to the ComponentManager.
     * @param entityManager Reference to the EntityManager.
     */
    void moveEntities(ComponentManager &componentManager, EntityManager &entityManager);

    /**
     * @brief Moves a single entity.
     *
     * This function updates the position of a specific entity based on its
     * movement component.
     *
     * @param componentManager Reference to the ComponentManager.
     * @param entityId The ID of the entity to be moved.
     */

    void moveEntity(ComponentManager &componentManager, int entityId);

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
     * for managing all entities within the ECS (Entity Component System). It provides
     * functionalities to create, destroy, and manage entities and their components.
     */
    EntityManager &_entityManager;
};
