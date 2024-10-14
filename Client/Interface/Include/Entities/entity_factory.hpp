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

class EntityFactory : public IEntityFactory {
  public:
    Entity createBackground(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager) override;
    Entity createPlayer(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager) override;
    Entity createMissile(int playerId, EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager) override;
    Entity createButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, std::string text, std::function<Scenes *(Scenes *)> onClick);
};