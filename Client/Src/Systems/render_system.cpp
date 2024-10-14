/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#include "Systems/render_system.hpp"

void RenderSystem::render(EntityManager &entityManager, ComponentManager &componentManager)
{
    _window.clear();
    const auto &entities = entityManager.getAllEntities();
    for (const auto &entity : entities) {
        auto spriteOpt = componentManager.getComponent<SpriteComponent>(entity.getId());

        if (spriteOpt) {
            _window.draw(spriteOpt.value()->sprite);
        }
        auto textOpt = componentManager.getComponent<TextComponent>(entity.getId());
        sf::Font font;
        font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF");
        if (textOpt) {
            _window.draw(sf::Text(textOpt.value()->_text, font));
        }
    }
    _window.display();
}
