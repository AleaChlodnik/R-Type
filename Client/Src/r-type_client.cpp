/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#include "Systems/systems.hpp"
#include <Components/component_manager.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <r_type_client.hpp>
#include <texture_manager.hpp>

Rtype::Rtype()
{
    currentGameMode = GameMode::EASY;
    currentDaltonismMode = DaltonismMode::NORMAL;
    main_menu = true;
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
    _window.create(
        sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close | sf::Style::Resize);
    _window.setFramerateLimit(60);

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
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);
    Entity player = entityFactory.createPlayer(entityManager, componentManager, textureManager);
    UpdateSystem updateSystem(_window);
    ShootSystem shootSystem(player.getId(), 0.5f);
    RenderSystem renderSystem(_window);

    sf::Clock clock;

    while (_window.isOpen()) {
        handleEvents();

        // MainMenu(_window);

        float deltaTime = clock.restart().asSeconds();

        // shootSystem.fireMissle(entityFactory, entityManager, componentManager, textureManager,
        // deltaTime); call only when specific key is pressed
        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);
    }
}
