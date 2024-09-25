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

    // Init player
    // Add player to systems
}

void Rtype::run()
{
    //while(true) {
        // if (main_menu)
            // mainMenu();
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
    // If you're joining an ongoing game instead of starting one, must know which allies and enemies are already in game and init before starting the game.

    _window.create(sf::VideoMode(800, 600), "R-Type");

    if (getDaltonismMode() != DaltonismMode::NORMAL) { // must test if filters are good
        sf::RectangleShape filter(sf::Vector2f(_window.getSize().x, _window.getSize().y));
        if (getDaltonismMode() == DaltonismMode::TRITANOPIA)
            filter.setFillColor(sf::Color(255, 255, 100, 100));
        else if (getDaltonismMode() == DaltonismMode::DEUTERANOPIA)
            filter.setFillColor(sf::Color(255, 100, 255, 100));
        else if (getDaltonismMode() == DaltonismMode::PROTANOPIA)
            filter.setFillColor(sf::Color(255, 255, 100, 100));
    }

    while (_window.isOpen()) {
        handleEvents();
    }
}
