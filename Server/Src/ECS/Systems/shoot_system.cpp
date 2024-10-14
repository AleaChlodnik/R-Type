/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** shoot_system
*/

#include "Systems/shoot_system.hpp"

void ShootSystem::fireMissle(EntityFactory entityFactory, EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, float deltaTime)
{
    this->_lastShotTime += deltaTime;
    if (this->_lastShotTime >= this->_fireRate) {
        entityFactory.createPlayerMissile(
            _playerId, entityManager, componentManager, textureManager);
        this->_lastShotTime = 0;
    }
}
