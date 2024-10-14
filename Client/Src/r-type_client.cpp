/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#include <ECS/Components/component_manager.hpp>
#include <ECS/Systems/systems.hpp>
#include <iostream>
#include <r_type_client.hpp>
#include <texture_manager.hpp>

Rtype::Rtype()
{
    _window.create(
        sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close | sf::Style::Resize);
    _window.setFramerateLimit(60);
    _scenes = new Scenes(&_window);
    // Init player
    // Add player to systems
};

void Rtype::run()
{
    while (!_scenes->shouldQuit() && _window.isOpen()) {
        _scenes->render();
    }
}

void Rtype::handleEvents()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _window.close();
        }
    }
}