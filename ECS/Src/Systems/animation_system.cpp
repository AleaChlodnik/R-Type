/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include <Systems/systems.hpp>

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

bool operator!=(AnimationComponent animation, AnimationComponent other)
{
    return (animation.offset.x != other.offset.x || animation.offset.y != other.offset.y ||
        animation.dimension.x != other.dimension.x || animation.dimension.y != other.dimension.y);
}

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
                if (velovity.value()->y < 0) {
                    animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_DOWN).x;
                } else if (velovity.value()->y > 0) {
                    animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_UP).x;
                }
                // } else {
                //     animation.value()->offset.x =
                //         animationShipFactory(AnimationShip::SHIP_STRAIT).x;
                // }
            }

            // animate system for background
            auto background = componentManager.getComponent<BackgroundComponent>(entity.getId());
            if (background) {
                animation.value()->offset.x += 5;
            }
        }
    }
}