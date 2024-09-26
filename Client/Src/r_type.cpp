/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#include "r_type.hpp"

Rtype::Rtype()
{
    currentGameMode = GameMode::EASY;
    currentDaltonismMode = DaltonismMode::NORMAL;
    main_menu = true;

    // Init background
    // Init player
    // Add player to systems
}

void Rtype::run()
{
    // while(true) {
    //  if (main_menu)
    //  mainMenu();
    // else
    gameLoop();
    //}
}

void Rtype::handleEvents()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void Rtype::gameLoop()
{
    _window.create(sf::VideoMode(800, 600), "R-Type");

    while (_window.isOpen()) {
        handleEvents();
    }
}
