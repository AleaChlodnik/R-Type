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

    // Draw sprites
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

                ///////////////////////////////////////////////////////////////////////////// Dont forget to remove
                sf::RectangleShape square(sf::Vector2f(sprite->hitboxX, sprite->hitboxY));
                square.setPosition(sprite->sprite.getPosition());
                square.setOrigin(sf::Vector2f(sprite->hitboxX / 2, sprite->hitboxY / 2));
                square.setOutlineColor(sf::Color::Red);
                square.setOutlineThickness(2.f);
                square.setFillColor(sf::Color::Transparent);
                _window.draw(square);
                /////////////////////////////////////////////////////////////////////////////

                _window.draw(sprite->sprite);
            }
        }
    }

    // Draw all texts
    const auto textComponents = componentManager.getComponentMap<TextComponent>();
    if (textComponents) {
        for (auto &pair : **textComponents) {
            auto &textComponentData = pair.second;
            if (auto *textComponent = std::any_cast<TextComponent>(&textComponentData)) {
                textComponent->text.setOrigin(textComponent->text.getLocalBounds().width / 2.0f,
                    textComponent->text.getLocalBounds().height / 2.0f);
                _window.draw(textComponent->text);
            }
        }
    }

    // Draw all rectangleShapes
    const auto rectangles = componentManager.getComponentMap<RectangleShapeComponent>();
    if (rectangles) {
        for (const auto &pair : **rectangles) {
            const auto &rectangleComponent = pair.second;
            auto rectangle = std::any_cast<RectangleShapeComponent>(&rectangleComponent);
            if (rectangle) {
                _window.draw(rectangle->rectangleShape);
            }
        }
    }

    _window.display();
}
