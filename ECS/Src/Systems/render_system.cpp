/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#include <Systems/render_system.hpp>

void RenderSystem::render(ComponentManager &componentManager)
{
    _window.clear();
    const auto sprites = componentManager.getComponentMap<SpriteComponent>();
    if (sprites) {
        for (const auto &pair : **sprites) { // Derefrences the optional and then the pointer
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
                _window.draw(sprite->sprite);
            }
        }
    }
    const auto text = componentManager.getComponentMap<TextComponent>();
    _window.display();
}
