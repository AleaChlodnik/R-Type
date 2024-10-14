/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** shoot_system
*/

#pragma once

#include "Entities/entity_factory.hpp"
#include "Systems/i_system.hpp"

class ShootSystem {
  public:
    ShootSystem(int playerId, float fireRate)
        : _playerId(playerId), _fireRate(fireRate), _lastShotTime(0){};

    void fireMissle(EntityFactory entityFactory, EntityManager &entityManager,
        ComponentManager &componentManager, TextureManager &textureManager, float deltaTime);

  private:
    int _playerId;
    float _fireRate;
    float _lastShotTime;
};
