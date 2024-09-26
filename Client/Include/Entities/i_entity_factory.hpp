/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity_factory
*/

#pragma once

#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/component_manager.hpp"

// Abstract Entity Factory
class IEntityFactory {
    public:
        virtual ~IEntityFactory() = default;

        virtual Entity createPlayer(EntityManager &entityManager, ComponentManager &componentManager) = 0;
};
