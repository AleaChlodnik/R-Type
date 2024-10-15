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

void Scenes::setScene(Scenes::Scene scene)
{
    this->previousScene = this->currentScene;
    this->currentScene = scene;
}

void handleEvents(sf::Event event, ComponentManager &componentManager, sf::RenderWindow *_window,
    std::vector<Entity *> buttons, Scenes *scenes)
{
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::MouseButtonPressed and
            event.mouseButton.button == sf::Mouse::Left) {
            auto pos = sf::Mouse::getPosition(*_window);
            for (auto button : buttons) {
                auto posComp = componentManager.getComponent<PositionComponent>(button->getId());
                auto sprite = componentManager.getComponent<SpriteComponent>(button->getId());
                if (sprite)
                    if (posComp && sprite) {
                        sf::Vector2u spriteSize = sprite.value()->sprite.getTexture()->getSize();
                        if (pos.x >= posComp.value()->x &&
                            pos.x <= posComp.value()->x + spriteSize.x &&
                            pos.y >= posComp.value()->y &&
                            pos.y <= posComp.value()->y + spriteSize.y) {
                            auto onClick =
                                componentManager.getComponent<OnClickComponent>(button->getId());
                            if (onClick)
                                onClick.value()->onClick(scenes);
                        }
                    }
            }
        }
    }
}

void Scenes::mainMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    buttons = {};

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

    buttons.push_back(&playButton);
    buttons.push_back(&settingsButton);
    buttons.push_back(&quitButton);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::MAIN_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

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

    RenderSystem renderSystem(*_window);

    sf::Event event;

    auto updatePlayerPosition = [&](const vf2d &delta) {
        EntityInformation desc = c.GetAPlayer(c.GetEntityID());
        r_type::net::Message<TypeMessage> msg;
        desc.vPos.x += delta.x;
        desc.vPos.y += delta.y;
        msg.header.id = TypeMessage::MoveEntityMessage;
        msg << desc;
        c.Send(msg);
    };

    while (_window->isOpen()) {
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
                case sf::Keyboard::Space: {
                    EntityInformation desc = c.GetAPlayer(c.GetEntityID());
                    r_type::net::Message<TypeMessage> msg;
                    desc.vPos.x += 50;
                    desc.vPos.y += 50;
                    msg.header.id = TypeMessage::CreateEntityMessage;
                    msg << desc;
                    c.Send(msg);
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
                }
            }
        } else {
            std::cout << "Server Down" << std::endl;
            _window->close();
            break;
        }

        renderSystem.render(componentManager);
    }
}

void Scenes::inGameMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    buttons = {};

    // Create background
    Entity background = entityFactory.createBackground(entityManager, componentManager);
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale);
    componentManager.addComponent<SpriteComponent>(background.getId(), spriteComponent);
    // Create the buttons
    std::function<Scenes *(Scenes *)> onResumeButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };
    Entity resumeButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Resume", &onResumeButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(resumeButton.getId());
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

    std::function<Scenes *(Scenes *)> onReturnToMainMenuButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::MAIN_MENU);
        return currentScene;
    };
    Entity returnToMainMenu = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Return To Main Menu", &onReturnToMainMenuButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(returnToMainMenu.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 500;
    }

    buttons.push_back(&resumeButton);
    buttons.push_back(&settingsButton);
    buttons.push_back(&returnToMainMenu);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::IN_GAME_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(componentManager);
    }
}

void createDaltonismChoiceButtons(std::vector<Entity *> buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> onNormalButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::NORMAL);
        return currentScene;
    };
    Entity normalButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Normal", &onNormalButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(normalButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 100;
    }

    std::function<Scenes *(Scenes *)> onTritanopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::TRITANOPIA);
        return currentScene;
    };
    Entity tritanopiaButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Tritanopia", &onTritanopiaButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(tritanopiaButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 250;
    }

    std::function<Scenes *(Scenes *)> onDeuteranopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::DEUTERANOPIA);
        return currentScene;
    };
    Entity deuteranopiaButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Deuteranopia", &onDeuteranopiaButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(deuteranopiaButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 400;
    }

    std::function<Scenes *(Scenes *)> onProtanopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::PROTANOPIA);
        return currentScene;
    };
    Entity protanopiaButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Protanopia", &onProtanopiaButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(protanopiaButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 550;
    }

    buttons.push_back(&normalButton);
    buttons.push_back(&tritanopiaButton);
    buttons.push_back(&deuteranopiaButton);
    buttons.push_back(&protanopiaButton);
}

void createGameModeChoiceButtons(std::vector<Entity *> buttons, ComponentManager &componentManager,
    EntityManager &entityManager, TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> easyButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::EASY);
        return currentScene;
    };
    Entity easyButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Easy", &easyButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(easyButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 250;
    }

    std::function<Scenes *(Scenes *)> mediumButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::MEDIUM);
        return currentScene;
    };
    Entity mediumButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Medium", &mediumButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(mediumButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 400;
    }

    std::function<Scenes *(Scenes *)> hardButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::HARD);
        return currentScene;
    };
    Entity hardButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Hard", &hardButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(hardButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 550;
    }

    buttons.push_back(&easyButton);
    buttons.push_back(&mediumButton);
    buttons.push_back(&hardButton);
}

// void createKeyBindingButtons()
// {
//     std::function<Scenes *(Scenes *)> bind = [] (Scenes *currentScene) {

//     }
// }

void Scenes::settingsMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    buttons = {};

    // Create background
    Entity background = entityFactory.createBackground(entityManager, componentManager);
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(0.4, 0.4);
    SpriteComponent spriteComponent(texture, 0, 0, scale);

    // Create the buttons
    std::function<Scenes *(Scenes *)> onDaltonismModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayDaltonismChoice = !currentScene->displayDaltonismChoice;
        currentScene->displayGameModeChoice = false;
        currentScene->settingsMenu();
        return currentScene;
    };
    Entity daltonismModeButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Daltonism Mode", &onDaltonismModeButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(daltonismModeButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 100;
    }

    std::function<Scenes *(Scenes *)> onGameModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayGameModeChoice = !currentScene->displayGameModeChoice;
        currentScene->displayDaltonismChoice = false;
        currentScene->settingsMenu();
        return currentScene;
    };
    Entity gameModeButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Game Mode", &onGameModeButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(gameModeButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 250;
    }

    // std::function<Scenes *(Scenes *)> onKeybindButtonClicked = [](Scenes *currentScene) {
    //     createKeyBindingButtons();
    //     currentScene->settingsMenu();
    //     return currentScene;
    // };
    // Entity backButton = entityFactory.createButton(
    //     entityManager, componentManager, textureManager, "Back", &onKeybindButtonClicked);
    // pos = componentManager.getComponent<PositionComponent>(backButton.getId());
    // if (pos) {
    //     pos.value()->x = 760;
    //     pos.value()->y = 400;
    // }

    std::function<Scenes *(Scenes *)> onBackButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(currentScene->getPreviousScene());
        return currentScene;
    };
    Entity backButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Back", &onBackButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(backButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 650;
    }

    buttons.push_back(&daltonismModeButton);
    buttons.push_back(&gameModeButton);
    buttons.push_back(&backButton);

    if (displayDaltonismChoice)
        createDaltonismChoiceButtons(
            buttons, componentManager, entityManager, textureManager, entityFactory);
    if (displayGameModeChoice)
        createGameModeChoiceButtons(
            buttons, componentManager, entityManager, textureManager, entityFactory);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::SETTINGS_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(componentManager);
    }
}

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