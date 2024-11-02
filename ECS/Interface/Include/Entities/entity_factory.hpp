/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#pragma once

#include "a_scenes.hpp"
#include "i_entity_factory.hpp"
#include "i_scenes.hpp"
#include <functional>
#include <game_struct.h>

/**
 * @class EntityFactory
 * @brief A factory class for creating various types of entities.
 *
 * The EntityFactory class provides methods to create different types of entities
 * such as background, player, enemies, missiles, buttons, and more. It utilizes
 * the provided entity manager and component manager to create and initialize
 * the entities with the necessary components.
 */
class EntityFactory : public IEntityFactory {
  public:
    /**
     * @brief Create a Background Level One object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    Entity createBackgroundLevelOne(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Create a Background Level Two object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    Entity createBackgroundLevelTwo(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Create a Background Level Three object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    Entity createBackgroundLevelThree(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Create a Background Menu object
     *
     * @param entityManager
     * @param componentManager
     * @return Entity
     */
    Entity createBackgroundMenu(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager) override;

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
    Entity createInfoBar(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates a player entity.
     *
     * This function creates a player entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @param nbrOfPlayers The number of players to create.
     * @return The created player entity.
     */
    Entity createPlayer(EntityManager &entityManager, ComponentManager &componentManager,
        int nbrOfPlayers) override;

    /**
     * @brief Creates a shooter enemy entity.
     *
     * This function creates a shooter enemy entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @param posX The x-coordinate position of the shooter enemy.
     * @param posY The y-coordinate position of the shooter enemy.
     * @return The created shooter enemy entity.
     */
    Entity createShooterEnemy(EntityManager &entityManager, ComponentManager &componentManager,
        int posX, int posY) override;

    /**
     * @brief Creates a basic monster entity.
     *
     * This function creates a basic monster entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @param posX The x-coordinate position of the basic monster.
     * @param posY The y-coordinate position of the basic monster.
     * @return The created basic monster entity.
     */
    Entity createBasicMonster(EntityManager &entityManager, ComponentManager &componentManager,
        int posX, int posY) override;

    /**
     * @brief Creates a player missile entity.
     *
     * This function creates a player missile entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the player missile
     * entity using the component manager.
     *
     * @param entityManager The entity manager to add the player missile entity to.
     * @param componentManager The component manager to initialize the components for the player
     * missile entity.
     * @param entityId The id of the entity that shoots the missile.
     * @return The created player missile entity.
     */
    Entity createPlayerMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    /**
     * @brief Creates a force weapon entity.
     *
     * This function creates a force weapon entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the force weapon
     * entity using the component manager.
     *
     * @param entityManager The entity manager to add the force weapon entity to.
     * @param componentManager The component manager to initialize the components for the force
     * weapon entity.
     * @param entityId The id of the entity that uses the force weapon.
     * @return The created force weapon entity.
     */
    Entity createForceWeapon(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    /**
     * @brief Creates a force missile entity.
     *
     * This function creates a force missile entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the force missile
     * entity using the component manager.
     *
     * @param entityManager The entity manager to add the force missile entity to.
     * @param componentManager The component manager to initialize the components for the force
     * missile entity.
     * @param entityId The id of the entity that shoots the force missile.
     * @return The created force missile entity.
     */
    Entity createForceMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    /**
     * @brief Creates a power-up blue laser crystal entity.
     *
     * This function creates a power-up blue laser crystal entity using the provided entity manager
     * and component manager.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @return The created power-up blue laser crystal entity.
     */
    Entity createPowerUpBlueLaserCrystal(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates a wall entity.
     *
     * This function creates a wall entity using the provided entity manager and component manager.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @param posX The x-coordinate position of the wall.
     * @param posY The y-coordinate position of the wall.
     * @return The created wall entity.
     */
    Entity createWall(EntityManager &entityManager, ComponentManager &componentManager, int posX,
        int posY) override;

    /**
     * @brief Creates a button entity.
     *
     * This function creates a button entity with the specified parameters.
     *
     * @param entityManager The entity manager to create the entity.
     * @param componentManager The component manager to add components to the entity.
     * @param textureManager The texture manager to load the button texture.
     * @param fontManager The font manager to load the button font.
     * @param text The text to display on the button.
     * @param onClick The function to be called when the button is clicked.
     * @param x The x-coordinate position of the button.
     * @param y The y-coordinate position of the button.
     * @return The created button entity.
     */
    Entity createButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *)> *onClick, float x = 0, float y = 0) override;

    /**
     * @brief Creates a small button entity.
     *
     * This function creates a small button entity with the specified parameters.
     *
     * @param entityManager The entity manager to create the entity.
     * @param componentManager The component manager to add components to the entity.
     * @param textureManager The texture manager to load the button texture.
     * @param fontManager The font manager to load the button font.
     * @param text The text to display on the button.
     * @param onClick The function to be called when the button is clicked.
     * @param x The x-coordinate position of the button.
     * @param y The y-coordinate position of the button.
     * @return The created small button entity.
     */
    Entity createSmallButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x = 0,
        float y = 0) override;

    /**
     * @brief Creates an enemy missile entity.
     *
     * This function creates an enemy missile entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @param entityId The id of the entity that shoots the missile.
     * @return The created enemy missile entity.
     */

    Entity createEnemyMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    /**
     * @brief Creates a filter entity.
     *
     * This function creates a filter entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @param mode The Daltonism mode for the filter.
     * @return The created filter entity.
     */
    Entity createFilter(EntityManager &entityManager, ComponentManager &componentManager,
        AScenes::DaltonismMode mode);

    Entity backgroundFactory(
        EntityManager &entityManager, ComponentManager &componentManager, GameState type);

    /**
     * @brief Creates a boss entity.
     *
     * This function creates a boss entity using the provided entity manager and component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created boss entity.
     */
    Entity createBoss(EntityManager &entityManager, ComponentManager &componentManager,
        EntityFactory &entityFactory);

    Entity createTailSegment(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    Entity createTailEnd(
        EntityManager &entityManager, ComponentManager &componentManager) override;
};
