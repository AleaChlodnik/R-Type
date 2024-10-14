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
#include <vector>

class EntityManager {
  public:
    Entity createEntity()
    {
        int id = (entityNb += 1);
        entities.emplace_back(id);
        return entities.back();
    }

    void removeEntity(int entityId)
    {
        auto it = std::remove_if(entities.begin(), entities.end(),
            [entityId](const Entity &entity) { return entity.getId() == entityId; });

        if (it != entities.end()) {
            entities.erase(it, entities.end());
        } else
            throw entityNotFound();
    }

    Entity &getEntity(int entityId)
    {
        for (auto &entity : entities) {
            if (entity.getId() == entityId) {
                return entity;
            }
        }
        throw entityNotFound();
    }

    const std::vector<Entity> &getAllEntities() const { return entities; }

  private:
    int entityNb = 0;
    std::vector<Entity> entities;
};
