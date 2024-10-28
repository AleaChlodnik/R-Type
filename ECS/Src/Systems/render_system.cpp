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
    std::vector<std::pair<int, SpriteComponent>> sortedSprites;
    for (const auto &pair : **sprites) {
        const auto &spriteComponent = pair.second;
        auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
        if (sprite) {
            sortedSprites.emplace_back(pair.first, *sprite);
        }
    }

    std::sort(sortedSprites.begin(), sortedSprites.end(), [](const auto &a, const auto &b) {
        return a.second.type < b.second.type;
    });

    for (const auto &pair : sortedSprites) {
        const auto &sprite = pair.second;
        _window.draw(sprite.sprite);
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
                        textToDraw.getLocalBounds().height);
                    textToDraw.setPosition(position.value()->x, position.value()->y);
                    _window.draw(textToDraw);
                }
            }
        }
    }

    // Draw all rectanglesShapes
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
