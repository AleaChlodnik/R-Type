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

    /**
     * @brief Pure virtual function to handle the logic for Level One.
     *
     * @param server Pointer to the server instance managing the game.
     * @param componentManager Reference to the ComponentManager handling game components.
     * @param entityManager Reference to the EntityManager handling game entities.
     * @param newClock The current time point used for time-based operations.
     */
    virtual void LevelOne(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Pure virtual function to handle the logic for Level Two.
     *
     * @param server Pointer to the server instance managing the game.
     * @param componentManager Reference to the ComponentManager handling game components.
     * @param entityManager Reference to the EntityManager handling game entities.
     * @param newClock The current time point used for time-based operations.
     */
    virtual void LevelTwo(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Pure virtual function to handle the logic for Level Three.
     *
     * @param server Pointer to the server instance managing the game.
     * @param componentManager Reference to the ComponentManager handling game components.
     * @param entityManager Reference to the EntityManager handling game entities.
     * @param newClock The current time point used for time-based operations.
     */
    virtual void LevelThree(r_type::net::AServer<T> *server, ComponentManager &componentManager,
        EntityManager &entityManager, std::chrono::system_clock::time_point newClock) = 0;

    /**
     * @brief Spawns a specified number of enemy entities in the game.
     *
     * @param server Pointer to the server instance managing the game.
     * @param entityManager Reference to the EntityManager responsible for handling entities.
     * @param componentManager Reference to the ComponentManager responsible for handling
     * components.
     * @param nbrOfEnemy The number of enemy entities to spawn.
     * @param enemyType The type of enemy to spawn, specified by the EnemyType enum.
     */
    virtual void SpawnEntity(r_type::net::AServer<T> *server, EntityManager &entityManager,
        ComponentManager &componentManager, int nbrOfEnemy,
        EntityFactory::EnemyType enemyType) = 0;

    /**
     * @brief Sets the game difficulty based on the provided game parameters.
     *
     * This function sets the game difficulty based on the provided game parameters.
     *
     * @param gameParameters The game parameters to set the difficulty.
     */
    virtual void SetGameParameters(GameParameters gameParameters) = 0;

    /**
     * @brief Get the Entity Back Ground object
     *
     * @param server
     * @param entityManager
     * @param componentManager
     * @return EntityInformation
     */
    virtual EntityInformation GetEntityBackGround(r_type::net::AServer<T> *server,
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Change the background object
     *
     * @param server
     * @param entityManager
     * @param componentManager
     * @return EntityInformation
     */
    virtual void ChangeBackground(r_type::net::AServer<T> *server,
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Initializes a background entity.
     *
     * The function creates and returns information about the background entity.
     *
     * @return EntityInformation The information of the background entity.
     */
    virtual EntityInformation InitiateBackground(r_type::net::AServer<T> *server,
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Changes the level of the game based on the provided game state.
     *
     * @param state
     */
    virtual void ChangeLevel(GameState state) = 0;

    /**
     * @brief Get the level object
     *
     * @return GameState
     */
    virtual GameState GetLevel() = 0;
};
} // namespace r_type
