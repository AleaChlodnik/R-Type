/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_manager
*/

#pragma once

#include "../error_handling.hpp"
#include "entity.hpp"
#include <vector>

class EntityManager {
  public:
    Entity createEntity()
    {
        int id = (entityNb += 1);
        entities.emplace_back(id);
        return entities.back();
    }

    Entity &getEntity(int id)
    {
        for (auto &entity : entities) {
            if (entity.getId() == id) {
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
