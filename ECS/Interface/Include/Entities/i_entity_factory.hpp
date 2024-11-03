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
    virtual Entity createBackgroundLevelOne(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Create a Background Level Two object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    virtual Entity createBackgroundLevelTwo(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Create a Background Level Three object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    virtual Entity createBackgroundLevelThree(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @brief Create a Background Menu object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    virtual Entity createBackgroundMenu(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager) = 0;

    /**
     * @brief Creates a bar entity.
     *
     * This function creates a bar with text for displaying player information like health and
     * score.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @return The created bar entity.
     */
    virtual Entity createInfoBar(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

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
        EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY) = 0;

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
        EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY) = 0;

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
     * @brief Creates a Force Weapon entity.
     *
     * This function is responsible for creating a Force Weapon entity and adding it to the
     * provided EntityManager and ComponentManager. The entity is identified by the given entityId.
     *
     * @param entityManager Reference to the EntityManager that will manage the entity.
     * @param componentManager Reference to the ComponentManager that will manage the components of
     * the entity.
     * @param entityId The unique identifier for the entity to be created.
     * @return Entity The created Force Weapon entity.
     */
    virtual Entity createForceWeapon(
        EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId) = 0;

    /**
     * @brief Creates a Force Missile entity.
     *
     * This function creates a Force Missile entity and registers it with the given
     * EntityManager and ComponentManager. The entity is identified by the provided
     * entityId.
     *
     * @param entityManager Reference to the EntityManager that will manage the entity.
     * @param componentManager Reference to the ComponentManager that will manage the components of
     * the entity.
     * @param entityId The unique identifier for the entity to be created.
     * @return Entity The created Force Missile entity.
     */
    virtual Entity createForceMissile(
        EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId) = 0;

    /**
     * @brief Creates a Power-Up Blue Laser Crystal entity.
     *
     * This function is responsible for creating an entity that represents a
     * Power-Up Blue Laser Crystal in the game. It initializes the entity with
     * the necessary components and registers it with the provided EntityManager
     * and ComponentManager.
     *
     * @param entityManager Reference to the EntityManager that will manage the entity.
     * @param componentManager Reference to the ComponentManager that will manage the components of
     * the entity.
     * @return Entity The created Power-Up Blue Laser Crystal entity.
     */
    virtual Entity createPowerUpBlueLaserCrystal(
        EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY) = 0;

    /**
     * @brief Creates a wall entity with the specified position.
     *
     * @param entityManager Reference to the EntityManager that will manage the new entity.
     * @param componentManager Reference to the ComponentManager that will manage the components of
     * the new entity.
     * @param posX The x-coordinate of the wall's position.
     * @param posY The y-coordinate of the wall's position.
     * @return Entity The created wall entity.
     */
    virtual Entity createWall(
        EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY) = 0;

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

    /**
     * @brief Creates a button entity with the specified properties.
     *
     * @param entityManager Reference to the EntityManager responsible for managing entities.
     * @param componentManager Reference to the ComponentManager responsible for managing
     * components.
     * @param textureManager Reference to the TextureManager responsible for managing textures.
     * @param fontManager Reference to the FontManager responsible for managing fonts.
     * @param text The text to be displayed on the button.
     * @param onClick A pointer to a function that will be called when the button is clicked.
     * @param x The x-coordinate position of the button.
     * @param y The y-coordinate position of the button.
     * @return Entity The created button entity.
     */
    virtual Entity createSmallButton(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager,
        FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x = 0,
        float y = 0) = 0;

    virtual Entity createUpdateButton(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager,
        FontManager &fontManager, std::string text, std::function<IScenes *(AScenes *)> *onClick,
        std::function<std::string(GameParameters)> *updateText, float x, float y) = 0;

    virtual Entity createTailSegment(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    virtual Entity createTailEnd(
        EntityManager &entityManager, ComponentManager &componentManager) = 0;

    /**
     * @enum EnemyType
     * @brief Enumeration representing different types of enemies in the game.
     *
     * This enumeration defines the various enemy types that can be instantiated
     * in the game. Each type corresponds to a specific kind of enemy with unique
     * behaviors and characteristics.
     *
     * @var EnemyType::BasicMonster
     * Basic enemy type with standard behavior.
     *
     * @var EnemyType::ShooterEnemy
     * Enemy type that can shoot projectiles.
     *
     * @var EnemyType::Wall
     * Stationary enemy type that acts as an obstacle.
     *
     * @var EnemyType::Boss
     * Boss enemy type with advanced behavior and higher difficulty.
     */
    enum EnemyType
    {
        BasicMonster,
        ShooterEnemy,
        Wall,
        Boss,
    };
};
