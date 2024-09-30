/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "texture_manager.hpp"
#include "entity_factory.hpp"
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

    if (getDaltonismMode() != DaltonismMode::NORMAL) { // must test if filters are good
        sf::RectangleShape filter(sf::Vector2f(_window.getSize().x, _window.getSize().y));
        if (getDaltonismMode() == DaltonismMode::TRITANOPIA)
            filter.setFillColor(sf::Color(255, 255, 100, 100));
        else if (getDaltonismMode() == DaltonismMode::DEUTERANOPIA)
            filter.setFillColor(sf::Color(255, 100, 255, 100));
        else if (getDaltonismMode() == DaltonismMode::PROTANOPIA)
            filter.setFillColor(sf::Color(255, 255, 100, 100));
    }

    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;

    Entity player = entityFactory.createPlayer(entityManager, componentManager, textureManager); ////////////////////// test

    //MessageHandler messageHandler(entityManager, componentManager, entityFactory);
    //UpdateSystem updateSystem(entityManager, componentManager); // Handles position updates, physics, etc.
    //RenderSystem renderSystem(entityManager, componentManager);

    while (_window.isOpen()) {
        handleEvents();
        
        ////////////////////////////////////////////////////////////// test
        _window.clear();
        auto playerId = player.getId();
        auto playerSprite = componentManager.getComponent<SpriteComponent>(playerId);
        _window.draw(playerSprite->sprite);
        _window.display();
    }
}
