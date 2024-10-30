/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity_factory
*/

#pragma once

#include "Components/component_manager.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "font_manager.hpp"
#include "texture_manager.hpp"

// Abstract Entity Factory
/**
 * @class IEntityFactory
 *
 * @brief The interface for an entity factory.
 *
 * This interface defines the methods for creating different types of entities in the game.
 * Each method takes references to the entity manager, component manager, and other necessary
 * parameters, and returns an entity object.
 *
 * @note This is an abstract base class and cannot be instantiated directly.
 */
class IEntityFactory {
  public:
    /**
     * @brief Destroy the IEntityFactory object
     *
     */
    virtual ~IEntityFactory() = default;

    /**
     * @brief Creates a background entity.
     *
     * This function creates a background entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @return The created background entity.
     */
    virtual Entity createBackground(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;
    
    /**
     * @brief Creates a bar entity.
     * 
     * This function creates a bar with text for displaying player information like health and score.
     * 
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @return The created bar entity.
     */
    virtual Entity createInfoBar(EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Creates a player entity.
     *
     * This function creates a player entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created player entity.
     */
    virtual Entity createPlayer(
        EntityManager &entityManager, ComponentManager &componentManager, int nbrOfPlayers) = 0;

    /**
     * @brief Creates a shooter enemy entity.
     *
     * This function creates a shooter enemy entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created shooter enemy entity.
     */
    virtual Entity createShooterEnemy(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Creates a basic monster entity.
     *
     * This function creates a basic monster entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created basic monster entity.
     */
    virtual Entity createBasicMonster(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Creates a player missile entity.
     *
     * This function creates a player missile entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the player missile
     * entity using the component manager.
     *
     * @param entityId The ID of the entity that shoot the missile.
     * @param entityManager The entity manager to add the player missile entity to.
     * @param componentManager The component manager to initialize the components for the player
     * missile entity.
     * @return The created player missile entity.
     */
    virtual Entity createPlayerMissile(
        EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId) = 0;

    /**
     * @brief Creates an enemy missile entity.
     *
     * This function creates an enemy missile entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created enemy missile entity.
     */
    virtual Entity createEnemyMissile(
        EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId) = 0;

    /**
     * @brief Creates a button entity.
     *
     * This function creates a button entity using the provided entity manager, component manager,
     * texture manager, text, and onClick function. The button entity represents a clickable button
     * in the game.
     *
     * @param entityManager The entity manager used to create the button entity.
     * @param componentManager The component manager used to manage the components of the button
     * entity.
     * @param textureManager The texture manager used to load the textures for the button entity.
     * @param text The text displayed on the button.
     * @param onClick The function to be called when the button is clicked.
     * @return The created button entity.
     */
    virtual Entity createButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *)> *onClick, float x, float y) = 0;

    virtual Entity createSmallButton(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager,
        FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x = 0,
        float y = 0) = 0;
};
