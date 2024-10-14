/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity_factory
*/

#pragma once

#include "entity.hpp"
#include "entity_manager.hpp"
#include "scenes.hpp"
#include "texture_manager.hpp"
#include <ECS/Components/component_manager.hpp>
#include <functional>

// Abstract Entity Factory
class IEntityFactory {
  public:
    virtual ~IEntityFactory() = default;

    virtual Entity createBackground(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createButtonEntityManager(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager, std::string text,
        std::function<Scenes *(Scenes *)> onClick) = 0;
};
