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
    if (text) {
        sf::Font font;
        font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF");
        for (const auto &pair : **text) {
            const auto &textComponent = pair.second;
            const int id = pair.first;
            auto text = std::any_cast<TextComponent>(&textComponent);
            if (text) {
                sf::Text textToDraw(text->_text, font);
                auto position = componentManager.getComponent<PositionComponent>(id);
                auto sprite = componentManager.getComponent<SpriteComponent>(id);
                if (sprite) {
                    sf::FloatRect spriteBounds = sprite.value()->sprite.getGlobalBounds();
                    sf::FloatRect textBounds = textToDraw.getGlobalBounds();
                    float x = position.value()->x + (spriteBounds.width / 2.0f) - (textBounds.width / 2.0f);
                    float y = position.value()->y + (spriteBounds.height / 2.0f) - textBounds.height;
                    textToDraw.setPosition(x, y);
                } else
                    textToDraw.setPosition(position.value()->x, position.value()->y);
                _window.draw(textToDraw);
            }
        }
    }
    _window.display();
}
