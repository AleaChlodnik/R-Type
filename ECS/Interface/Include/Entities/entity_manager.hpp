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
 *
 * @brief Class responsible for managing entities in the ECS system.
 *
 */
class EntityManager {
  public:
    /**
     * @brief Create a Entity object
     *
     * @return Entity
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
    std::vector<Entity> entities;
};
