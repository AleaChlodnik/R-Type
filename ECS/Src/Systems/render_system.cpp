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

    // Draw all sprites
    const auto sprites = componentManager.getComponentMap<SpriteComponent>();
    if (sprites) {
        // Draw background first
        for (const auto &pair : **sprites) {
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
                if (sprite->type == AScenes::SpriteType::BACKGROUND) {
                    _window.draw(sprite->sprite);
                    break;
                }
            }
        }
        // Draw all other sprites
        for (const auto &pair : **sprites) {
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
                if (sprite->type == AScenes::SpriteType::BACKGROUND) {
                    continue;
                }

                sf::RectangleShape square(sf::Vector2f(sprite->hitboxX, sprite->hitboxY));
                square.setPosition(sprite->sprite.getPosition());
                square.setOrigin(sf::Vector2f(sprite->hitboxX / 2, sprite->hitboxY / 2));
                square.setOutlineColor(sf::Color::Red);
                square.setOutlineThickness(2.f);
                square.setFillColor(sf::Color::Transparent);
                _window.draw(square);

                _window.draw(sprite->sprite);
            }
        }
    }

    // Draw all texts
    const auto texts = componentManager.getComponentMap<TextComponent>();
    if (texts) {
        for (const auto &pair : **texts) {
            const int id = pair.first;
            const auto &textComponent = pair.second;
            auto text = std::any_cast<TextComponent>(&textComponent);
            if (text) {
                sf::Text textToDraw(text->_text, _font);
                auto position = componentManager.getComponent<PositionComponent>(id);
                if (position) {
                    textToDraw.setOrigin(textToDraw.getLocalBounds().width / 2.0f,
                        textToDraw.getLocalBounds().height / 2.0f);
                    textToDraw.setPosition(position.value()->x, position.value()->y);
                    _window.draw(textToDraw);
                }
            }
        }
    }

    _window.display();
}
