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

/**
 * @brief Construct a new Rtype:: Rtype object
 *
 */
Rtype::Rtype(std::string ip, int port)
{
    _window.create(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close);
    _window.setFramerateLimit(60);
    _scenes = new Scenes(&_window, ip, port);
};

void Rtype::run()
{
    while (!_scenes->shouldQuit() && _window.isOpen()) {
        _scenes->render();
    }
}
