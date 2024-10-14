/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#include "ECS/Systems/render_system.hpp"

void RenderSystem::render(ComponentManager &componentManager)
{
    _window.clear();
    const auto sprites = componentManager.getComponentMap<SpriteComponent>();
    if (sprites) {
        for (const auto &sprite : sprites.value()) {
            _window.draw(sprite.second->sprite);
        }
    }
    _window.display();
}
