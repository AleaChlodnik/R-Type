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

/**
 * @class EntityFactory
 *
 * @brief A class responsible for creating different types of entities.
 */
class EntityFactory : public IEntityFactory {
  public:
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
    Entity createBackground(
        EntityManager &entityManager, ComponentManager &componentManager) override;

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
     * @return The created basic enemy entity.
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
     * @return The created basic monster entity.
     */
    Entity createBasicMonster(EntityManager &entityManager, ComponentManager &componentManager,
        int posX, int posY) override;

    /**
     * @brief Creates a player missile entity.
     *
     *
     * This function creates a player missile entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the player missile
     * entity using the component manager.
     *
     * @param entityManager The entity manager to add the player missile entity to.
     * @param componentManager The component manager to initialize the components for the player
     * @param entityId The id of the entity that shoot the missile
     * @return The created player missile entity.
     */
    Entity createPlayerMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    Entity createForceWeapon(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    Entity createForceMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;

    Entity createPowerUpBlueLaserCrystal(
        EntityManager &entityManager, ComponentManager &componentManager) override;
    /**
     * @brief Creates a button entity.
     *
     * This function creates a button entity with the specified parameters.
     *
     * @param entityManager The entity manager to create the entity.
     * @param componentManager The component manager to add components to the entity.
     * @param textureManager The texture manager to load the button texture.
     * @param text The text to display on the button.
     * @param onClick The function to be called when the button is clicked.
     *
     * @return The created button entity.
     *
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
     * @param text The text to display on the button.
     * @param onClick The function to be called when the button is clicked.
     *
     * @return The created small button entity.
     *
     */
    Entity createSmallButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, std::string text,
        std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x = 0,
        float y = 0) override;
    /**
     * @brief Creates an ally missile entity.
     *
     * This function creates an ally missile entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to manage the components of the
     * entity.
     * @return The created ally missile entity.
     *
     */

    /**
     * @brief Creates an enemy missile entity.
     *
     *
     * This function creates an enemy missile entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @param entityId The id of the entity that shoot the missile
     * @return The created enemy missile entity.
     */
    Entity createEnemyMissile(EntityManager &entityManager, ComponentManager &componentManager,
        uint32_t entityId) override;
    /**
     * @brief Create a Filter object
     *
     * @param entityManager
     * @param componentManager
     * @param mode
     * @return Entity
     */
    Entity createFilter(EntityManager &entityManager, ComponentManager &componentManager,
        AScenes::DaltonismMode mode);
};
