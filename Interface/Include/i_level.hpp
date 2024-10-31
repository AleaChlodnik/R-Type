/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_level
*/

#pragma once

#include <Net/i_server.hpp>

/**
 * @file ILevel.hpp
 * @brief Interface for level management in the r_type game.
 */

namespace r_type {

/**
 * @namespace net
 * @brief Contains networking-related classes for the r_type game.
 */
namespace net {

/**
 * @brief AServer class template for network management.
 * @tparam T The type parameter for AServer.
 */
template <typename T> class AServer;

} // namespace net

/**
 * @class ILevel
 * @brief Interface class for defining levels in the r_type game.
 * @tparam T The type parameter for AServer.
 */
template <typename T> class ILevel {
  public:
    /**
     * @brief Virtual destructor for the ILevel interface.
     */
    virtual ~ILevel() = default;

    /**
     * @brief Updates the level based on the server state, component manager, entity manager, and
     * time.
     * @param server Pointer to the AServer instance.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param newClock The current time point for updating.
     * @param bUpdateEntities Flag to indicate whether to update entities.
     */
    virtual void Update(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock,
        bool *bUpdateEntities) = 0;

    /**
     * @brief Sets up the system with the given component and entity managers.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     */
    virtual void SetSystem(ComponentManager &componentManager, EntityManager &entityManager) = 0;

    /**
     * @brief Handles movement updates in the level.
     * @param server Pointer to the AServer instance.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param newClock The current time point for updating movement.
     */
    virtual void MoveUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Updates animations in the level.
     * @param server Pointer to the AServer instance.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param newClock The current time point for updating animations.
     */
    virtual void AnimationUpdate(r_type::net::AServer<T> *server,
        ComponentManager &componentManager, EntityManager &entityManager,
        std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Manages firing updates in the level.
     * @param server Pointer to the AServer instance.
     * @param componentManager Reference to the ComponentManager instance.
     * @param entityManager Reference to the EntityManager instance.
     * @param newClock The current time point for updating firing actions.
     */
    virtual void FireUpdate(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Updates the collision state of the game entities.
     *
     * This function is responsible for updating the collision state of the game entities
     * within the server. It takes into account the current state of the component manager,
     * entity manager, and the new clock time point to perform the necessary updates.
     *
     * @tparam T The type of the server.
     * @param server Pointer to the server instance.
     * @param componentManager Reference to the component manager.
     * @param entityManager Reference to the entity manager.
     * @param newClock The new clock time point for the update.
     */
    virtual void CollisionUpdate(r_type::net::AServer<T> *server,
        ComponentManager &componentManager, EntityManager &entityManager,
        std::chrono::system_clock::time_point newClock) = 0;

    virtual void LevelOne(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;
};
enum class TypeLevel
{
    LevelOne,
    LevelTwo,
    LevelThree,
    LevelFour,
};
} // namespace r_type
