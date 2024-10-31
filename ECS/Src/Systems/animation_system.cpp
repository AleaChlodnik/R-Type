/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include <Systems/systems.hpp>

/**
 * @brief Generates a vector representing the animation state of a ship.
 *
 * This function takes an AnimationShip enumeration value and returns a
 * vf2d vector that corresponds to the animation state of the ship.
 *
 * @param animation The animation state of the ship, represented by the
 * AnimationShip enumeration.
 *
 * @return vf2d A vector representing the animation state of the ship.
 * The x-coordinate of the vector corresponds to the frame position,
 * and the y-coordinate is always -1 for valid states. If the animation
 * state is not recognized, the function returns {0, 0}.
 */
vf2d animationShipFactory(AnimationShip animation)
{
    switch (animation) {
    case AnimationShip::SHIP_DOWN: {
        return {0, -1};
    } break;
    case AnimationShip::SHIP_FLIP_DOWN: {
        return {33.2, -1};
    } break;
    case AnimationShip::SHIP_STRAIT: {
        return {66.4, -1};
    } break;
    case AnimationShip::SHIP_FLIP_UP: {
        return {99.6, -1};
    } break;
    case AnimationShip::SHIP_UP: {
        return {132.8, -1};
    } break;
    }
    return {0, 0};
}

vf2d animationBasicMonsterFactory(AnimationBasicMonster animation)
{
    switch (animation) {
    case AnimationBasicMonster::BASIC_MONSTER_DEFAULT: {
        return {0, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_1: {
        return {32.8, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_2: {
        return {32.8 * 2, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_3: {
        return {32.8 * 3, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_4: {
        return {32.8 * 4, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_5: {
        return {32.8 * 5, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_6: {
        return {32.8 * 6, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_7: {
        return {32.8 * 7, -1};
    } break;
    }
    return {0, 0};
}

vf2d animationWeapon1Factory(AnimationWeapon1 animation)
{
    switch (animation) {
    case AnimationWeapon1::WEAPON_1_DEFAULT: {
        return {300 + 0, -1};
    } break;
    case AnimationWeapon1::WEAPON_1_1: {
        return {300 + 24, -1};
    } break;
    case AnimationWeapon1::WEAPON_1_2: {
        return {300 + 24 * 2, -1};
    } break;
    case AnimationWeapon1::WEAPON_1_3: {
        return {300 + 24 * 3, -1};
    } break;
    case AnimationWeapon1::WEAPON_1_4: {
        return {300 + 24 * 4, -1};
    } break;
    case AnimationWeapon1::WEAPON_1_5: {
        return {300 + 24 * 5, -1};
    } break;
    }
    return {0, 0};
}

/**
 * @brief Inequality operator for AnimationComponent.
 *
 * This operator compares two AnimationComponent objects to determine if they are not equal.
 * Two AnimationComponent objects are considered not equal if any of their respective
 * offset or dimension coordinates differ.
 *
 * @param animation The first AnimationComponent to compare.
 * @param other The second AnimationComponent to compare.
 * @return true if the AnimationComponent objects are not equal, false otherwise.
 */
bool operator!=(AnimationComponent animation, AnimationComponent other)
{
    return (animation.offset.x != other.offset.x || animation.offset.y != other.offset.y ||
        animation.dimension.x != other.dimension.x || animation.dimension.y != other.dimension.y);
}

/**
 * @brief Updates the animation states of entities based on their components.
 *
 * This function iterates through all entities and updates their animation
 * states based on the presence and values of specific components such as
 * AnimationComponent, PlayerComponent, VelocityComponent, and BackgroundComponent.
 *
 * @param componentManager Reference to the ComponentManager that handles components.
 * @param entityManager Reference to the EntityManager that handles entities.
 * @param deltaTime The time elapsed since the last update, used for time-based animations.
 */
void AnimationSystem::AnimationEntities(
    ComponentManager &componentManager, EntityManager &entityManager, float deltaTime)
{
    for (auto entity : entityManager.getAllEntities()) {

        auto animation = componentManager.getComponent<AnimationComponent>(entity.getId());
        if (animation) {
            // animate system for ship
            auto player = componentManager.getComponent<PlayerComponent>(entity.getId());
            auto velocity = componentManager.getComponent<VelocityComponent>(entity.getId());
            if (player && velocity) {
                animatePlayer(velocity, animation);
            }

            // animate system for basic monster
            auto basicMonster =
                componentManager.getComponent<BasicMonsterComponent>(entity.getId());
            if (basicMonster) {
                animateBasicMonster(animation);
            }

            // animate system for weapon
            auto weapon = componentManager.getComponent<WeaponComponent>(entity.getId());
            if (weapon) {
                animateWeapon(animation);
            }

            // animate system for background
            auto background = componentManager.getComponent<BackgroundComponent>(entity.getId());
            if (background) {
                animation.value()->offset.x += 1;
            }
        }
    }
}

void AnimationSystem::animatePlayer(
    std::optional<VelocityComponent *> &velocity, std::optional<AnimationComponent *> &animation)
{
    if (velocity.value()->y >= -1 && velocity.value()->y < -0.6) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_DOWN).x;
    } else if (velocity.value()->y >= -0.6 && velocity.value()->y < -0.2) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_FLIP_DOWN).x;
    } else if (velocity.value()->y >= -0.2 && velocity.value()->y < 0.2) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_STRAIT).x;
    } else if (velocity.value()->y >= 0.2 && velocity.value()->y < 0.6) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_FLIP_UP).x;
    } else if (velocity.value()->y >= 0.6 && velocity.value()->y < 1) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_UP).x;
    }
    if (velocity.value()->y < 0) {
        velocity.value()->y += 0.05;
    } else if (velocity.value()->y > 0) {
        velocity.value()->y -= 0.05;
    }
}

void AnimationSystem::animateBasicMonster(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_DEFAULT).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_1).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_1).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_2).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_2).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_3).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_3).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_4).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_4).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_5).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_5).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_6).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_6).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_7).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_7).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_DEFAULT).x;
    }
}

void AnimationSystem::animateWeapon(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_DEFAULT).x) {
        animation.value()->offset.x = animationWeapon1Factory(AnimationWeapon1::WEAPON_1_1).x;
    } else if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_1).x) {
        animation.value()->offset.x = animationWeapon1Factory(AnimationWeapon1::WEAPON_1_2).x;
    } else if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_2).x) {
        animation.value()->offset.x = animationWeapon1Factory(AnimationWeapon1::WEAPON_1_3).x;
    } else if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_3).x) {
        animation.value()->offset.x = animationWeapon1Factory(AnimationWeapon1::WEAPON_1_4).x;
    } else if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_4).x) {
        animation.value()->offset.x = animationWeapon1Factory(AnimationWeapon1::WEAPON_1_5).x;
    } else if (animation.value()->offset.x ==
        animationWeapon1Factory(AnimationWeapon1::WEAPON_1_5).x) {
        animation.value()->offset.x =
            animationWeapon1Factory(AnimationWeapon1::WEAPON_1_DEFAULT).x;
    }
}
