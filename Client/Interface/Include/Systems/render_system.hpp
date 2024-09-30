/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Components/components.hpp"
#include "Entities/entity_manager.hpp"
#include <SFML/Graphics.hpp>

class RenderSystem {
  public:
    RenderSystem(sf::RenderWindow &window) : _window(window) {}

    void render(EntityManager &entityManager, ComponentManager &componentManager)
    {
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
