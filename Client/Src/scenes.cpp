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
    this->currentScene = Scenes::Scene::MAIN_MENU;
    // this->currentScene = Scenes::Scene::GAME_LOOP; ////// TEMPORARY
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
    EntityFactory entityFactory;
    sf::Clock clock;
    Entity background = entityFactory.createBackground(entityManager, componentManager);
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale);
    componentManager.addComponent<SpriteComponent>(background.getId(), spriteComponent);
    /////////////////////////////////////////////////////////////////////////////////// TEMPORARY

    auto updatePlayerPosition = [&](const vf2d &delta) {
        EntityInformation desc = c.GetAPlayer(c.GetEntityID());
        r_type::net::Message<TypeMessage> msg;
        desc.vPos.x += delta.x;
        desc.vPos.y += delta.y;
        msg.header.id = TypeMessage::MoveEntityMessage;
        msg << desc;
        c.Send(msg);
    };

    auto fireMissile = [&]() {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::CreateEntityMessage;
        msg << CreatableClientObject::MISSILE;
        c.Send(msg);
    };

    while (_window->isOpen()) {
        float deltaTime =
            clock.restart().asSeconds(); /////////////////////////////////////// TEMPORARY
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::DestroyEntityMessage;
                msg << c.GetEntityID();
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
                    // Tell server to create missile from player position
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
                    c.AddEntity(entity);
                    c.SetEntityID(entity.uniqueID);
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
                    c.AddEntity(entity);
                } break;
                case TypeMessage::CreateEntityResponse: {
                } break;
                case TypeMessage::DestroyEntityMessage: {
                    r_type::net::Message<TypeMessage> reponse;
                    uint32_t id;
                    msg >> id;
                    c.RemoveEntity(id);
                    reponse.header.id = TypeMessage::DestroyEntityResponse;
                    c.Send(reponse);
                } break;
                case TypeMessage::UpdateEntity: {
                    r_type::net::Message<TypeMessage> reponse;
                    reponse.header.id = TypeMessage::UpdateEntityResponse;
                    EntityInformation entity;
                    msg >> entity;
                    c.UpdateEntity(entity);
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
        updateSystem.update(entityManager, componentManager, 0.0f);
        renderSystem.render(componentManager);
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