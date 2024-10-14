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
    }
    _window.display();
}
