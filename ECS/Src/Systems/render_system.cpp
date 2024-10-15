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
        auto bgSpriteIt = sprites.find(1);
        if (bgSpriteIt != sprites.end()) {
            const auto &spriteComponent = bgSpriteIt->second;
            auto bgSprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (bgSprite) {
                _window.draw(bgSprite->sprite);
            }
        }

        for (const auto &pair : sprites) { // Derefrences the optional and then the pointer
            int entityId = pair.first;
            if (entityId == backgroundId || entityId == 1) {
                continue;
            }
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
                _window.draw(sprite->sprite);
            }
        }
    }
    _window.display();
}
