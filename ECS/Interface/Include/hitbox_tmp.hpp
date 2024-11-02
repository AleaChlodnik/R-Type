/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** hitbox_tmp
*/

#pragma once
#include <Components/component_manager.hpp>
#include <Entities/entity.hpp>
#include <Entities/entity_manager.hpp>
#include <entity_struct.hpp>

/**
 * @brief Checks the position of an entity within the game world.
 *
 * This function retrieves and checks the position of the specified entity
 * using the provided component and entity managers.
 *
 * @param entityId The unique identifier of the entity whose position is to be checked.
 * @param componentManager The manager responsible for handling components of entities.
 * @param entityManager The manager responsible for handling entities.
 * @return An integer representing the status or result of the position check.
 */
int CheckEntityPosition(
    uint32_t entityId, ComponentManager componentManager, EntityManager entityManager);

/**
 * @brief Checks the movement of an entity within the game.
 *
 * @param desc An EntityInformation object containing details about the entity.
 * @param componentManager A ComponentManager object to manage the components of entities.
 * @param entityManager An EntityManager object to manage the entities.
 * @return An integer indicating the result of the movement check.
 */
int CheckEntityMovement(
    EntityInformation desc, ComponentManager componentManager, EntityManager entityManager);
