/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity
*/

#pragma once

/**
 * @class Entity
 *
 * @brief Represents an entity in the ECS system.
 *
 * This class is a concrete implementation of the IEntity interface.
 * It provides functionality to retrieve the ID of the entity.
 */
class Entity {
  public:
    /**
     * @brief Constructs an Entity object with the given ID.
     *
     * @param id The ID of the entity.
     */
    explicit Entity(int id) : _id(id) {}

    /**
     * @brief Returns the ID of the entity.
     *
     *
     * @return The ID of the entity.
     */
    int getId() const { return _id; }

  private:
    int _id;
};
