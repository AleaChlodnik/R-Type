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
        for (const auto &pair : **sprites) { // Derefrences the optional and then the pointer
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
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

// int entityId = pair.first;
// if (entityId == backgroundId || entityId == 1) {
//     continue;
// }

// Always display background first - menus
// int backgroundId = 0;
// auto backgroundOpt = componentManager.getComponentMap<BackgroundComponent>();
// if (backgroundOpt) {
//     auto &backgroundMap = **backgroundOpt;
//     if (!backgroundMap.empty()) {
//         auto entityId = backgroundMap.begin()->first;
//         backgroundId = entityId;
//     }
//     auto bgSprite = componentManager.getComponent<SpriteComponent>(backgroundId);
//     _window.draw(bgSprite.value()->sprite);
// }
// Always display background first - game
// auto bgSpriteIt = sprites.find(1);
// if (bgSpriteIt != sprites.end()) {
//     const auto &spriteComponent = bgSpriteIt->second;
//     auto bgSprite = std::any_cast<SpriteComponent>(&spriteComponent);
//     if (bgSprite) {
//         _window.draw(bgSprite->sprite);
//     }
// }
