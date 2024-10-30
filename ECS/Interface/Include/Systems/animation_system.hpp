/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#pragma once

#include "../entity_struct.hpp"
#include "Systems/i_system.hpp"

/**
 * @brief Represents the animation component.
 * @var AnimationComponent::offset The offset of the animation.
 * @var AnimationComponent::dimension The dimension of the animation.
 */
enum class AnimationShip : uint32_t
{
    /**
     * @brief Ship animation when going down.
     */
    SHIP_DOWN,
    /**
     * @brief Ship animation when flipping down.
     */
    SHIP_FLIP_DOWN,
    /**
     * @brief Ship animation when going strait.
     */
    SHIP_STRAIT,
    /**
     * @brief Ship animation when flipping up.
     */
    SHIP_FLIP_UP,
    /**
     * @brief Ship animation when going up.
     */
    SHIP_UP
};

enum class AnimationBasicMonster : uint32_t
{
    BASIC_MONSTER_DEFAULT,
    BASIC_MONSTER_1,
    BASIC_MONSTER_2,
    BASIC_MONSTER_3,
    BASIC_MONSTER_4,
    BASIC_MONSTER_5,
    BASIC_MONSTER_6,
    BASIC_MONSTER_7
};

/**
 * @brief get if two animations are different.
 *
 * @param  animation The first animation.
 * @param  other The second animation.
 *
 * @return  bool true if the animations are different, false otherwise.
 */
bool operator!=(AnimationComponent animation, AnimationComponent other);

/**
 * @brief Factory function to create a ship animation.
 *
 * This function takes an AnimationShip object and generates a corresponding
 * vf2d object that represents the animation of the ship.
 *
 * @param animation The AnimationShip object containing the animation details.
 * @return vf2d The generated animation for the ship.
 */
vf2d animationShipFactory(AnimationShip animation);

class AnimationSystem : public ISystem {
  public:
    AnimationSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager){};

    /**
     * @brief Animates entities.
     *
     * This function animates entities based on their animation components. It processes
     * each entity in the entity manager and updates their animation based on the delta
     * time provided.
     *
     * @param componentManager The component manager used to access entity components.
     * @param entityManager The entity manager used to access entities.
     * @param deltaTime The time elapsed since the last update, used to update animations.
     */
    void AnimationEntities(
        ComponentManager &componentManager, EntityManager &entityManager, float deltaTime);

  private:
    /**
     * @brief Reference to the ComponentManager instance.
     *
     * This member variable holds a reference to the ComponentManager, which is
     * responsible for managing all the components within the ECS (Entity Component System).
     * It provides functionality to add, remove, and query components associated with entities.
     */
    ComponentManager &_componentManager;
    /**
     * @brief Reference to the EntityManager instance.
     *
     * This member variable holds a reference to the EntityManager, which is responsible
     * for managing all entities within the ECS (Entity Component System). It provides
     * functionalities such as entity creation, deletion, and retrieval.
     */
    EntityManager &_entityManager;
};
