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
        // std::cout << "render can access unordered map of sprites" << std::endl; //////////////////////////////////
        auto &sprites = **spritesOpt;
        // Always display background first - game
            const auto &spriteComponent = sprites[2];
            auto bgSprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (bgSprite) {
                // std::cout << "Got bg sprite" << std::endl; /////////////////////////////////////////////////
                _window.draw(bgSprite->sprite);
            }

        for (const auto &pair : sprites) { // Derefrences the optional and then the pointer
            int entityId = pair.first;
            // std::cout << "Entity ID: " << entityId << std::endl; /////////////////////////////////////////////////
            if (entityId == backgroundId) { // || entityId == 2
                continue;
            }
            const auto &spriteComponent = pair.second;
            auto sprite = std::any_cast<SpriteComponent>(&spriteComponent);
            if (sprite) {
                // std::cout << "Got bg sprite" << std::endl; /////////////////////////////////////////////////
                _window.draw(sprite->sprite);
            }
        }
    }
    _window.display();
}
