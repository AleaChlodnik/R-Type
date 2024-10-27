/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** move_system
*/

#pragma once

#include "../entity_struct.hpp"
#include "Systems/i_system.hpp"

enum class AnimationShip : uint32_t
{
    SHIP_DOWN,
    SHIP_FLIP_DOWN,
    SHIP_STRAIT,
    SHIP_FLIP_UP,
    SHIP_UP
};

bool operator!=(AnimationComponent animation, AnimationComponent other);

vf2d animationShipFactory(AnimationShip animation);

class AnimationSystem : public ISystem {
  public:
    AnimationSystem(ComponentManager &componentManager, EntityManager &entityManager)
        : _componentManager(componentManager), _entityManager(entityManager){};

    void update(float deltaTime) override
    {
        AnimationEntities(this->_componentManager, this->_entityManager, deltaTime);
    };

    void AnimationEntities(
        ComponentManager &componentManager, EntityManager &entityManager, float deltaTime);

  private:
    ComponentManager &_componentManager;
    EntityManager &_entityManager;
};
