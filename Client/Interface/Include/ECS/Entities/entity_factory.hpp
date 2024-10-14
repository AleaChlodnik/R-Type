/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#pragma once

#include "i_entity_factory.hpp"

class EntityFactory : public IEntityFactory {
  public:
    Entity createBackground(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager) override;
    Entity createButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, std::string text,
        std::function<Scenes *(Scenes *)> onClick);
};
