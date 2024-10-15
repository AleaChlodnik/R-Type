/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#include <Components/component_manager.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Systems/systems.hpp>
#include <iostream>
#include <r_type_client.hpp>
#include <texture_manager.hpp>

Rtype::Rtype()
{
    _window.create(
        sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close | sf::Style::Resize);
    _window.setFramerateLimit(60);
    _scenes = new Scenes(&_window);
};

void Rtype::run()
{
    while (!_scenes->shouldQuit() && _window.isOpen()) {
        _scenes->render();
    }
}
