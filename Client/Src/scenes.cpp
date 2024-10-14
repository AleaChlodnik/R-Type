/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#include <Components/component_manager.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Systems/systems.hpp>
#include <functional>
#include <iostream>
#include <r_type_client.hpp>
#include <scenes.hpp>
#include <texture_manager.hpp>

Scenes::Scenes(sf::RenderWindow *window)
{
    this->_window = window;
    this->currentScene = Scenes::Scene::MAIN_MENU;
}

void Scenes::setScene(Scenes::Scene scene) { this->currentScene = scene; }

void Scenes::mainMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);
    // Create the buttons
    std::function<Scenes *(Scenes *)> onClickPlay = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };

    Entity playButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Play", onClickPlay);
    auto pos = componentManager.getComponent<PositionComponent>(playButton.getId());
    if (pos) {
        pos.value()->x = 100;
        pos.value()->y = 100;
    }
    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::MAIN_MENU) {

        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left) {
                auto pos = sf::Mouse::getPosition(*_window);
                auto posComp =
                    componentManager.getComponent<PositionComponent>(playButton.getId());
                auto sprite = componentManager.getComponent<SpriteComponent>(playButton.getId());
                auto size = sprite.value()->sprite.getTexture()->getSize();
                if (posComp && sprite) {
                    if (pos.x >= posComp.value()->x && pos.x <= posComp.value()->x + size.x &&
                        pos.y >= posComp.value()->y && pos.y <= posComp.value()->y + size.y) {
                        auto onClick = componentManager.getComponent<OnClickComponent>(playButton.getId());
                        if (onClick) {
                            std::cout << "Button clicked" << std::endl;
                            onClick.value()->onClick(this);
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);
    }
}

void Scenes::gameLoop()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);
    Entity player = entityFactory.createPlayer(entityManager, componentManager, textureManager);
    ShootSystem shootSystem(player.getId(), 0.5f);
    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    shootSystem.fireMissle(
                        entityFactory, entityManager, componentManager, textureManager, deltaTime);
                };
                if (event.key.code == sf::Keyboard::Up) {
                    auto posOpt = componentManager.getComponent<PositionComponent>(player.getId());
                    if (posOpt) {
                        posOpt.value()->y -= 5;
                    }
                }
                if (event.key.code == sf::Keyboard::Down) {
                    auto posOpt = componentManager.getComponent<PositionComponent>(player.getId());
                    if (posOpt) {
                        posOpt.value()->y += 5;
                    }
                }
                if (event.key.code == sf::Keyboard::Left) {
                    auto posOpt = componentManager.getComponent<PositionComponent>(player.getId());
                    if (posOpt) {
                        posOpt.value()->x -= 5;
                    }
                }
                if (event.key.code == sf::Keyboard::Right) {
                    auto posOpt = componentManager.getComponent<PositionComponent>(player.getId());
                    if (posOpt) {
                        posOpt.value()->x += 5;
                    }
                }
            }
        }

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);
    }
}

void Scenes::inGameMenu() { return; }

void Scenes::settingsMenu() { return; }

void Scenes::render()
{
    switch (this->currentScene) {
    case Scenes::Scene::MAIN_MENU:
        this->mainMenu();
        break;
    case Scenes::Scene::GAME_LOOP:
        this->gameLoop();
        break;
    case Scenes::Scene::SETTINGS_MENU:
        this->settingsMenu();
        break;
    case Scenes::Scene::IN_GAME_MENU:
        this->inGameMenu();
        break;
    default:
        break;
    }
}