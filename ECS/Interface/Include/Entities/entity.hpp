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
     * @brief Constructs an Entity with a specified ID.
     *
     * @param id The unique identifier for the entity.
     */
    explicit Entity(int id) : _id(id) {}

    /**
     * @brief Retrieves the unique identifier of the entity.
     *
     * @return int The unique identifier of the entity.
     */
    int getId() const { return _id; }

  private:
    /**
     * @brief Unique identifier for the entity.
     */
    int _id;
};
