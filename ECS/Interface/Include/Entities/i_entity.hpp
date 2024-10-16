/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity
*/

#pragma once

/**
 * @class IEntity
 *
 * @brief The IEntity class represents an entity in the system.
 *
 * This class provides an interface for entities in the system. It defines
 * a pure virtual function getId() which returns the ID of the entity.
 *
 * @note This class is meant to be inherited from and should not be instantiated directly.
 */
class IEntity {
  public:
    /**
     * @brief Destructor for the IEntity class.
     */
    virtual ~IEntity() = default;
    /**
     * @brief Gets the ID of the entity.
     *
     * @return The ID of the entity.
     */
    virtual int getId() const = 0;
};
