/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#pragma once

#include "i_entity_factory.hpp"
#include "scenes.hpp"
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
     * @brief Creates a player entity.
     * 
     * This function creates a player entity using the provided entity manager and component manager.
     * 
     * @param entityManager The entity manager to use for creating the entity.
     * @param componentManager The component manager to use for adding components to the entity.
     * @return The created player entity.
     */
    Entity createPlayer(
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
    Entity createAlly(EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates a basic enemy entity.
     *
     * This function creates a basic enemy entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created basic enemy entity.
     */
    Entity createBasicEnemy(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates a basic monster entity.
     *
     * This function creates a basic monster entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created basic monster entity.
     */
    Entity createBasicMonster(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates a player missile entity.
     *
     *
     * This function creates a player missile entity with the specified player ID and adds it to
     * the entity manager. It also initializes the necessary components for the player missile
     * entity using the component manager.
     *
     * @param playerId The ID of the player.
     * @param entityManager The entity manager to add the player missile entity to.
     * @param componentManager The component manager to initialize the components for the player
     * missile entity.
     * @return The created player missile entity.
     */
    Entity createPlayerMissile(
        int playerId, EntityManager &entityManager, ComponentManager &componentManager) override;

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
        TextureManager &textureManager, std::string text,
        std::function<Scenes *(Scenes *)> *onClick);

    /**
     * @brief Creates an ally missile entity.
     *
     * This function creates an ally missile entity using the provided entity manager and component
     * manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to manage the components of the entity.
     * @return The created ally missile entity.
     *
     */
    Entity createAllyMissile(
        EntityManager &entityManager, ComponentManager &componentManager) override;

    /**
     * @brief Creates an enemy missile entity.
     *
     *
     * This function creates an enemy missile entity using the provided entity manager and
     * component manager.
     *
     * @param entityManager The entity manager used to create the entity.
     * @param componentManager The component manager used to add components to the entity.
     * @return The created enemy missile entity.
     */
    Entity createEnemyMissile(
        EntityManager &entityManager, ComponentManager &componentManager) override;
};
