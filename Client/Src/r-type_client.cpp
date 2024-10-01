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
    _window.create(
        sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Close | sf::Style::Resize);

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
    RenderSystem renderSystem(_window);

    sf::Clock clock;

    /////////////////////////////////////////////////////// test
    Entity player1 = entityFactory.createPlayer(entityManager, componentManager, textureManager);
    Entity player2 = entityFactory.createPlayer(entityManager, componentManager, textureManager);
    Entity player3 = entityFactory.createPlayer(entityManager, componentManager, textureManager);

    componentManager.addComponent<PositionComponent>(player2.getId(), 400, 400);
    componentManager.addComponent<PositionComponent>(player3.getId(), 800, 800);
    //////////////////////////////////////////////////////////

    while (_window.isOpen()) {
        handleEvents();

        float deltaTime = clock.restart().asSeconds();

        // renderSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);

        /////////////////////////////////////////////////////// test
        auto player1Pos = componentManager.getComponent<PositionComponent>(player1.getId());
        auto player2Pos = componentManager.getComponent<PositionComponent>(player2.getId());
        auto player3Pos = componentManager.getComponent<PositionComponent>(player3.getId());
        componentManager.addComponent<PositionComponent>(
            player1.getId(), player1Pos.value()->x + 1, player1Pos.value()->y);
        componentManager.addComponent<PositionComponent>(
            player2.getId(), player2Pos.value()->x + 1, player2Pos.value()->y);
        componentManager.addComponent<PositionComponent>(
            player3.getId(), player3Pos.value()->x + 1, player3Pos.value()->y);
    }
}
