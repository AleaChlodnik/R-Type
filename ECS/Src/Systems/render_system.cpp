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

    // Always display background first - menus
    int backgroundId = 0;
    auto backgroundOpt = componentManager.getComponentMap<BackgroundComponent>();
    if (backgroundOpt) {
        auto &backgroundMap = **backgroundOpt;
        if (!backgroundMap.empty()) {
            auto entityId = backgroundMap.begin()->first;
            backgroundId = entityId;
        }
        auto bgSprite = componentManager.getComponent<SpriteComponent>(backgroundId);
        _window.draw(bgSprite.value()->sprite);
    }

    const auto spritesOpt = componentManager.getComponentMap<SpriteComponent>();
    if (spritesOpt) {

        auto &sprites = **spritesOpt;

        // Always display background first - game
        // if (sprites.find(serverBackgroundId) != sprites.end()) {
        //     const auto &anySprite = sprites[serverBackgroundId];
        //     auto spriteComponent = std::any_cast<SpriteComponent>(&anySprite);
        //     if (spriteComponent) {
        //         _window.draw(spriteComponent->sprite);
        //     }
        // }

        for (const auto &pair : sprites) { // Derefrences the optional and then the pointer
            const auto &entityId = pair.first;
            if (entityId == backgroundId) { // || entityId == (serverBackgroundId)
                continue;
            }
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
                textToDraw.setOrigin(textToDraw.getLocalBounds().width / 2.0f, textToDraw.getLocalBounds().height / 2.0f);
                textToDraw.setPosition(position.value()->x, position.value()->y);
                _window.draw(textToDraw);
            }
        }
    }
    _window.display();
}
