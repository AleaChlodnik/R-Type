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
    default:
        return {0, 0};
    }
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
            auto velovity = componentManager.getComponent<VelocityComponent>(entity.getId());
            if (player && velovity) {
                if (velovity.value()->y >= -1 && velovity.value()->y < -0.6) {
                    std::cout << "UP" << std::endl;
                    animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_DOWN).x;
                } else if (velovity.value()->y >= -0.6 && velovity.value()->y < -0.2) {
                    animation.value()->offset.x =
                        animationShipFactory(AnimationShip::SHIP_FLIP_DOWN).x;
                } else if (velovity.value()->y >= -0.2 && velovity.value()->y < 0.2) {
                    animation.value()->offset.x =
                        animationShipFactory(AnimationShip::SHIP_STRAIT).x;
                } else if (velovity.value()->y >= 0.2 && velovity.value()->y < 0.6) {
                    animation.value()->offset.x =
                        animationShipFactory(AnimationShip::SHIP_FLIP_UP).x;
                } else if (velovity.value()->y >= 0.6 && velovity.value()->y < 1) {
                    animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_UP).x;
                }
                // } else {
                //     animation.value()->offset.x =
                //         animationShipFactory(AnimationShip::SHIP_STRAIT).x;
                // }
                if (velovity.value()->y < 0) {
                    velovity.value()->y += 0.05;
                } else {
                    velovity.value()->y -= 0.05;
                }
            }

            // animate system for background
            auto background = componentManager.getComponent<BackgroundComponent>(entity.getId());
            if (background) {
                animation.value()->offset.x += 5;
            }
        }
    }
}