/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Components/components.hpp"
#include "Entities/entity_manager.hpp"
#include "Systems/i_system.hpp"

/**
 * @class UpdateSystem
 *
 * @brief A system responsible for updating entities in the game.
 */
class UpdateSystem : public ISystem {
  public:
    UpdateSystem(sf::RenderWindow &window) : _window(window) {}

    void update(EntityManager &entityManager, ComponentManager &componentManager, float deltaTime);

    void updateSpritePosition(EntityManager &entityManager, ComponentManager &componentManager);
    void updateBackground(ComponentManager &componentManager, float deltaTime);

    // bool updatePlayerMissile(int entityId, EntityManager &entityManager,
    //     ComponentManager &componentManager, float deltaTime);

    void setGameBgOffset(int offset) { gameBgOffset = offset; }
    int getGameBgOffset() { return gameBgOffset; }

  private:
    sf::RenderWindow &_window;
    int gameBgOffset = 0;
};
