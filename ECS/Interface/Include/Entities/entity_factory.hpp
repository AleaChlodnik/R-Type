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
    Entity createBackground(
        EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createPlayer(EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createAlly(EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createBasicEnemy(
        EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createBasicMonster(
        EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createPlayerMissile(
        int playerId, EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, std::string text,
        std::function<Scenes *(Scenes *)> *onClick);
    Entity createSmallButton(EntityManager &entityManager, ComponentManager &componentManager,
        TextureManager &textureManager, std::string text,
        std::function<Scenes *(Scenes *, Scenes::Actions)> *onClick);
    Entity createAllyMissile(EntityManager &entityManager, ComponentManager &componentManager) override;
    Entity createEnemyMissile(EntityManager &entityManager, ComponentManager &componentManager) override;
};
