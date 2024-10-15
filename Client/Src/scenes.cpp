/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Net/client.hpp>
#include <Systems/systems.hpp>
#include <creatable_client_object.hpp>
#include <functional>
#include <iostream>
#include <r_type_client.hpp>
#include <scenes.hpp>
#include <texture_manager.hpp>

Scenes::Scenes(sf::RenderWindow *window)
{
    this->_window = window;
    // this->currentScene = Scenes::Scene::MAIN_MENU;
    this->currentScene = Scenes::Scene::GAME_LOOP; ////// TEMPORARY
}

/**
 * @brief Set the Scene object
 *
 * @param scene
 */
void Scenes::setScene(Scenes::Scene scene) { this->currentScene = scene; }

/**
 * @brief Displays the main menu scene.
 *
 * This function creates the main menu scene, including the background, buttons, and event
 * handling. The main menu scene allows the user to navigate to different scenes by clicking on the
 * buttons. The buttons include "Play", "Settings", and "Quit". The function continuously updates
 * and renders the scene until the user closes the window or navigates to a different scene.
 *
 * @return void
 */
void Scenes::mainMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    // Create background
    Entity background = entityFactory.createBackground(entityManager, componentManager);
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale);
    componentManager.addComponent<SpriteComponent>(background.getId(), spriteComponent);
    // Create buttons
    std::function<Scenes *(Scenes *)> onPlayButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };
    Entity playButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Play", &onPlayButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(playButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 100;
    }

    std::function<Scenes *(Scenes *)> onSettingsButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::SETTINGS_MENU);
        return currentScene;
    };
    Entity settingsButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Settings", &onSettingsButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(settingsButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 250;
    }

    std::function<Scenes *(Scenes *)> onQuitButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::EXIT);
        return currentScene;
    };
    Entity quitButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Quit", &onQuitButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(quitButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 500;
    }

    std::vector<Entity *> buttons = {&playButton, &settingsButton, &quitButton};

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::MAIN_MENU) {
        float deltaTime = clock.restart().asSeconds();
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::MouseButtonPressed and
                event.mouseButton.button == sf::Mouse::Left) {
                auto pos = sf::Mouse::getPosition(*_window);
                for (auto button : buttons) {
                    auto posComp =
                        componentManager.getComponent<PositionComponent>(button->getId());
                    auto sprite = componentManager.getComponent<SpriteComponent>(button->getId());
                    auto size = sprite.value()->sprite.getTexture()->getSize();
                    if (posComp && sprite) {
                        if (pos.x >= posComp.value()->x && pos.x <= posComp.value()->x + size.x &&
                            pos.y >= posComp.value()->y && pos.y <= posComp.value()->y + size.y) {
                            auto onClick =
                                componentManager.getComponent<OnClickComponent>(button->getId());
                            if (onClick)
                                onClick.value()->onClick(this);
                        }
                    }
                }
            }
        }
        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(componentManager);
    }
}

/**
 * @brief This function handles the main game loop for the Scenes class. It contains the logic for
 * connecting to a server, updating entities, handling user input, and rendering the game.
 *
 * @details The game loop performs the following steps:
 * 1. Connects to a server using the r_type::net::Client class.
 * 2. Initializes the ComponentManager, TextureManager, and EntityManager.
 * 3. Creates a background entity and sets its sprite component.
 * 4. Defines lambda functions for updating player position and firing missiles.
 * 5. Enters the main loop, which continues until the window is closed.
 * 6. Within the loop, it checks for user input events and handles them accordingly.
 * 7. If the server is connected, it processes incoming messages and updates entities accordingly.
 * 8. It then updates the entities using the UpdateSystem and renders them using the RenderSystem.
 *
 * @note This code assumes the presence of the r_type::net::Client, ComponentManager,
 * TextureManager, EntityManager, UpdateSystem, and RenderSystem classes.
 *
 * @see r_type::net::Client
 * @see ComponentManager
 * @see TextureManager
 * @see EntityManager
 * @see UpdateSystem
 * @see RenderSystem
 */
void Scenes::gameLoop()
{
    r_type::net::Client c;
    c.Connect("127.0.0.1", 60000);

    ComponentManager componentManager;
    TextureManager textureManager;
    EntityManager entityManager;

    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);

    sf::Event event;

    /////////////////////////////////////////////////////////////////////////////////// TEMPORARY
    sf::Clock clock;
    /////////////////////////////////////////////////////////////////////////////////// TEMPORARY

    auto updatePlayerPosition = [&](const vf2d &delta) {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::MoveEntityMessage;
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto spriteComponent = sprites[c.getPlayerId()];
            auto playerSprite = std::any_cast<SpriteComponent>(&spriteComponent);
            int playerPosX = playerSprite->sprite.getPosition().x;
            int playerPosY = playerSprite->sprite.getPosition().y;
            msg << vf2d{playerPosX + delta.x, playerPosY + delta.y};
        }
    };

    auto fireMissile = [&]() {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::CreateEntityMessage;
        msg << CreatableClientObject::MISSILE << c.getPlayerId();
        c.Send(msg);
    };

    while (_window->isOpen()) {
        float deltaTime =
            clock.restart().asSeconds(); /////////////////////////////////////// TEMPORARY
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::DestroyEntityMessage;
                msg << c.getPlayerId();
                c.Send(msg);
                _window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::P: {
                    c.PingServer();
                } break;
                case sf::Keyboard::Q: {
                    _window->close();
                } break;
                case sf::Keyboard::V: {
                    c.MessageAll();
                } break;
                case sf::Keyboard::Up: {
                    updatePlayerPosition(vf2d{0, -5});
                } break;
                case sf::Keyboard::Down: {
                    updatePlayerPosition(vf2d{0, 5});
                } break;
                case sf::Keyboard::Left: {
                    updatePlayerPosition(vf2d{-5, 0});
                } break;
                case sf::Keyboard::Right: {
                    updatePlayerPosition(vf2d{5, 0});
                } break;
                case sf::Keyboard::Space: {
                    fireMissile();
                } break;
                default:
                    break;
                }
            }
        }
        if (c.IsConnected()) {
            if (!c.Incoming().empty()) {
                auto msg = c.Incoming().pop_front().msg;
                switch (msg.header.id) {
                case TypeMessage::ServerAccept: {
                    std::cout << "Server Accepted Connection" << std::endl;
                    EntityInformation entity;
                    msg >> entity;
                    c.setPlayerId(entity.uniqueID);
                    c.addEntity(entity, componentManager, textureManager);

                } break;
                case TypeMessage::ServerPing: {
                    std::chrono::system_clock::time_point timeNow =
                        std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout << "Ping: "
                              << std::chrono::duration<double>(timeNow - timeThen).count()
                              << std::endl;
                } break;
                case TypeMessage::ServerMessage: {
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]" << std::endl;
                } break;
                case TypeMessage::ServerDeny: {
                } break;
                case TypeMessage::MessageAll: {
                } break;
                case TypeMessage::ClientConnect: {
                } break;
                case TypeMessage::CreateEntityMessage: {
                    EntityInformation entity;
                    msg >> entity;
                    c.addEntity(entity, componentManager, textureManager);
                } break;
                case TypeMessage::CreateEntityResponse: {
                } break;
                case TypeMessage::DestroyEntityMessage: {
                    r_type::net::Message<TypeMessage> reponse;
                    uint32_t id;
                    msg >> id;
                    c.removeEntity(id, componentManager);
                    reponse.header.id = TypeMessage::DestroyEntityResponse;
                    c.Send(reponse);
                } break;
                case TypeMessage::UpdateEntity: {
                    r_type::net::Message<TypeMessage> reponse;
                    reponse.header.id = TypeMessage::UpdateEntityResponse;
                    EntityInformation entity;
                    msg >> entity;
                    c.updateEntity(entity, componentManager);
                } break;
                case TypeMessage::UpdateEntityResponse: {
                } break;
                case TypeMessage::MoveEntityMessage: {
                } break;
                case TypeMessage::MoveEntityResponse: {
                } break;
                case TypeMessage::DestroyEntityResponse: {
                } break;
                }
            }
        } else {
            std::cout << "Server Down" << std::endl;
            _window->close();
            break;
        }
        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(componentManager);
    }
}

/**
 * @brief Displays the in-game menu.
 *
 */
void Scenes::inGameMenu() { return; }

/**
 * @brief Displays the settings menu.
 *
 * This function is responsible for displaying the settings menu in the game.
 * It does not return any value.
 */
void Scenes::settingsMenu() { return; }

/**
 * @brief Renders the current scene based on the value of currentScene.
 *
 * The render function uses a switch statement to determine which scene to render.
 * It calls the corresponding member function based on the value of currentScene.
 *
 * @note The currentScene variable must be set before calling this function.
 */
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