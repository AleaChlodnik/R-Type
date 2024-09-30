/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Entities/entity_manager.hpp"
#include "Components/component_manager.hpp"
#include "Components/components.hpp"

class RenderSystem {
  public:
    RenderSystem(sf::RenderWindow &window) : _window(window) {}

    void render(EntityManager &entityManager, ComponentManager &componentManager) {
        _window.clear();

        const auto &entities = entityManager.getAllEntities();

        for (const auto &entity : entities) {
            auto spriteOpt = componentManager.getComponent<SpriteComponent>(entity.getId());
            if (spriteOpt) {
                _window.draw(spriteOpt.value()->sprite);
            }
        }
        _window.display();
    }

  private:
    sf::RenderWindow &_window;
};
