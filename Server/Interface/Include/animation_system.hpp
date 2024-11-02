/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#pragma once

#include <entity_struct.hpp>
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

enum class AnimationForceWeapon1 : uint32_t
{
    FORCE_WEAPON_DEFAULT,
    FORCE_WEAPON_1,
    FORCE_WEAPON_2,
    FORCE_WEAPON_3,
    FORCE_WEAPON_4,
    FORCE_WEAPON_5
};

enum class AnimationForceWeapon2 : uint32_t
{
    FORCE_WEAPON_DEFAULT,
    FORCE_WEAPON_1,
    FORCE_WEAPON_2,
    FORCE_WEAPON_3,
    FORCE_WEAPON_4,
    FORCE_WEAPON_5
};

enum class AnimationForceWeapon3 : uint32_t
{
    FORCE_WEAPON_DEFAULT,
    FORCE_WEAPON_1,
    FORCE_WEAPON_2,
    FORCE_WEAPON_3
};

enum class AnimationForceMissile1 : uint32_t
{
    FORCE_MISSILE_DEFAULT
};

enum class AnimationForceMissile2 : uint32_t
{
    FORCE_MISSILE_DEFAULT
};

enum class AnimationForceMissile3 : uint32_t
{
    FORCE_MISSILE_DEFAULT,
    FORCE_MISSILE_1,
    FORCE_MISSILE_2,
    FORCE_MISSILE_3,
    FORCE_MISSILE_4,
    FORCE_MISSILE_5,
    FORCE_MISSILE_6,
    FORCE_MISSILE_7
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

/**
 * @class AnimationSystem
 * @brief A system responsible for animating entities within the ECS framework.
 *
 * The AnimationSystem class provides functionality to animate various entities
 * such as players, basic monsters, force weapons, and force missiles. It interacts
 * with the ComponentManager and EntityManager to access and update the relevant
 * components required for animation.
 *
 * @details
 * The AnimationSystem class inherits from the ISystem interface and implements
 * several methods to handle the animation of different types of entities. It
 * processes entities based on their animation components and updates their
 * animation states according to the provided delta time or specific component
 * states.
 *
 * @note
 * This class assumes the presence of specific components such as VelocityComponent,
 * AnimationComponent, and ForceWeaponComponent to perform the animations. The
 * methods use optional pointers to these components to ensure that animations
 * are only performed when the components are available.
 *
 * @see ISystem
 * @see ComponentManager
 * @see EntityManager
 */
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

    /**
     * @brief Animates the player based on their velocity.
     *
     * This function updates the player's animation state according to the provided
     * velocity component. If the velocity component indicates movement, the animation
     * component will be updated to reflect the corresponding animation state.
     *
     * @param velocity A reference to an optional VelocityComponent pointer. If the
     *                 pointer is present, it contains the player's current velocity.
     * @param animation A reference to an optional AnimationComponent pointer. If the
     *                  pointer is present, it contains the player's current animation state.
     */
    void animatePlayer(std::optional<VelocityComponent *> &velocity,
        std::optional<AnimationComponent *> &animation);

    /**
     * @brief Animates a basic monster entity.
     *
     * This function updates the animation state of a basic monster entity
     * based on the provided AnimationComponent. The animation state is
     * modified to reflect the current frame or sequence in the animation.
     *
     * @param animation An optional pointer to the AnimationComponent associated
     *                  with the basic monster entity. If the optional is empty,
     *                  no animation will be performed.
     */
    void animateBasicMonster(std::optional<AnimationComponent *> &animation);

    /**
     * @brief Animates the force weapon based on its current state.
     *
     * This function updates the animation of the force weapon component
     * by modifying the associated animation component.
     *
     * @param forceWeapon An optional reference to the ForceWeaponComponent.
     * @param animation An optional reference to the AnimationComponent.
     */
    void animateForceWeapon(std::optional<ForceWeaponComponent *> &forceWeapon,
        std::optional<AnimationComponent *> &animation);

    /**
     * @brief Animates the force missile based on the provided components.
     *
     * This function updates the animation state of a force missile using the
     * provided ForceWeaponComponent and AnimationComponent. The function
     * ensures that the animation reflects the current state of the force missile.
     *
     * @param forceWeapon An optional reference to a ForceWeaponComponent pointer.
     *                    This component contains the state and properties of the
     *                    force missile weapon.
     * @param animation An optional reference to an AnimationComponent pointer.
     *                  This component handles the animation state and frames
     *                  for the force missile.
     */
    void animateForceMissile(std::optional<ForceWeaponComponent *> &forceWeapon,
        std::optional<AnimationComponent *> &animation);

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
