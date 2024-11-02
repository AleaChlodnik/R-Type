/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_manager
*/

#pragma once

#include "../error_handling.hpp"
#include "entity.hpp"
#include <algorithm>
#include <memory>
#include <optional>
#include <vector>

/**
 * @class EntityManager
 * @brief Manages the creation, removal, and retrieval of entities.
 *
 * The EntityManager class is responsible for managing entities within the system. It provides
 * functionality to create new entities, remove existing ones, and retrieve entities by their ID.
 * It also allows access to all entities currently managed by the entity manager.
 */
class EntityManager {
  public:
    /**
     * @brief Creates a new entity and adds it to the entity manager.
     *
     * This function increments the entity counter, assigns a new unique ID to the entity,
     * and adds it to the list of managed entities.
     *
     * @return Entity The newly created entity.
     */
    Entity createEntity()
    {
        int id = (entityNb += 1);
        entities.emplace_back(id);
        return entities.back();
    }

    /**
     * @brief Remove an entity from the entity manager.
     *
     * @param entityId The ID of the entity to remove.
     *
     * This function removes the entity with the specified ID from the entity manager. If the
     * entity is not found, an entityNotFound exception is thrown.
     */
    void removeEntity(int entityId)
    {
        auto it = std::remove_if(entities.begin(), entities.end(),
            [entityId](const Entity &entity) { return entity.getId() == entityId; });

        if (it != entities.end()) {
            entities.erase(it, entities.end());
        } else
            throw entityNotFound();
    }

    /**
     * @brief Remove all entities from the entity manager.
     *
     * This function removes all entities from the entity manager.
     */
    void removeAllEntities()
    {
        if (entities.empty())
            return;
        std::cout << "Removing all entities" << std::endl;
        entities.clear();
        entityNb = 0;
    }

    /**
     * @brief Get an entity by its ID.
     *
     * @param entityId The ID of the entity to retrieve.
     * @return Entity& A reference to the entity with the specified ID.
     *
     * This function retrieves the entity with the specified ID from the entity manager. If the
     * entity is not found, an entityNotFound exception is thrown.
     */
    std::optional<Entity *> getEntity(int entityId)
    {
        for (auto &entity : entities) {
            if (entity.getId() == entityId) {
                return &entity;
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Get all entities in the entity manager.
     *
     * @return const std::vector<Entity>& A reference to the vector of entities.
     *
     * This function returns a reference to the vector of entities in the entity manager.
     */
    const std::vector<Entity> &getAllEntities() const { return entities; }

  private:
    /**
     * @brief The number of entities in the entity manager.
     *
     */
    int entityNb = 0;
    /**
     * @brief A container that holds a collection of Entity objects.
     *
     * This vector is used to manage and store all the entities within the
     * Entity Component System (ECS). Each Entity represents a unique object
     * within the ECS framework.
     */
    std::vector<Entity> entities;
};
