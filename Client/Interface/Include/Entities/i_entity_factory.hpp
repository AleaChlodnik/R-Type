/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity_factory
*/

#pragma once

#include "entity.hpp"
#include "entity_manager.hpp"
#include "texture_manager.hpp"
#include "Components/component_manager.hpp"

// Abstract Entity Factory
class IEntityFactory {
  public:
    virtual ~IEntityFactory() = default;

    virtual Entity createBackground(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createPlayer(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &TextureManager) = 0;
    virtual Entity createAlly(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &TextureManager) = 0;
    virtual Entity createBasicEnemy(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createBasicMonster(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createPlayerMissile(int playerId, EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createAllyMissile(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
    virtual Entity createEnemyMissile(EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &TextureManager) = 0;
};
