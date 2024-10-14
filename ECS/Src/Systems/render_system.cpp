/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** render_system
*/

#include <Systems/render_system.hpp>

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
            auto spriteOpt = componentManager.getComponent<SpriteComponent>(entity.getId());
            if (spriteOpt) {
                sf::FloatRect spriteBounds = spriteOpt.value()->sprite.getGlobalBounds();
                sf::Text text = sf::Text(textOpt.value()->_text, font);
                sf::FloatRect textBounds = text.getGlobalBounds();
                text.setPosition(
                    spriteBounds.left + (spriteBounds.width / 2.0f) - (textBounds.width / 2.0f),
                    spriteBounds.top + (spriteBounds.height / 2.0f) - textBounds.height);
                _window.draw(text);
            } else
                _window.draw(sf::Text(textOpt.value()->_text, font));
        }
    }
    _window.display();
}
