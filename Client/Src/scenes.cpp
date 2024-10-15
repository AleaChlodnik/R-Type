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
}

/**
 * @brief Set the Scene object
 *
 * @param scene
 */
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
                if (sprite) {
                    if (posComp && sprite) {
                        sf::Vector2u spriteSize = sprite.value()->sprite.getTexture()->getSize();
                        if (pos.x >= posComp.value()->x - spriteSize.x / 2 &&
                            pos.x <= posComp.value()->x + spriteSize.x / 2 &&
                            pos.y >= posComp.value()->y - spriteSize.y / 2 &&
                            pos.y <= posComp.value()->y + spriteSize.y / 2) {
                            auto onClick =
                                componentManager.getComponent<OnClickComponent>(button->getId());
                            if (onClick)
                                onClick.value()->onClick(scenes);
                            else {
                                auto bind =
                                    componentManager.getComponent<BindComponent>(button->getId());
                                if (bind) {
                                    auto it = std::find(buttons.begin(), buttons.end(), button);
                                    if (it != buttons.end()) {
                                        int index = std::distance(buttons.begin(), it);
                                        bind.value()->bind(scenes, Scenes::Actions(index));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

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
        pos.value()->x = 960;
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
        pos.value()->x = 960;
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
        pos.value()->x = 960;
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

    sf::Clock clock; ///////////////////////////////////////////////////// TEMPORARY

    auto updatePlayerPosition = [&](const vf2d &delta) {
        r_type::net::Message<TypeMessage> msg;
        std::cout << "Updating Player Position" << std::endl;
        vf2d playerPos;
        msg.header.id = TypeMessage::MoveEntityMessage;
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto spriteComponent = sprites[c.getPlayerId()];
            auto playerSprite = std::any_cast<SpriteComponent>(&spriteComponent);
            playerPos.x = playerSprite->sprite.getPosition().x + delta.x;
            playerPos.y = playerSprite->sprite.getPosition().y + delta.y;
            msg << playerPos;
            c.Send(msg);
        }
    };

    auto fireMissile = [&]() {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::CreateEntityMessage;
        msg << CreatableClientObject::MISSILE;
        c.Send(msg);
    };

    auto death = [&]() {
        std::cout << "Closing window" << std::endl;
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::DestroyEntityMessage;
        msg << c.getPlayerId();
        c.Send(msg);
        _window->close();
    };

    while (_window->isOpen()) {
        float deltaTime =
            clock.restart().asSeconds(); /////////////////////////////////////// TEMPORARY
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                death();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    c.PingServer();
                }
                if (event.key.code == sf::Keyboard::V) {
                    c.MessageAll();
                }
                if (event.key.code == keyBinds[Actions::FIRE]) {
                    fireMissile();
                }
                if (event.key.code == keyBinds[Actions::QUIT]) {
                    _window->close();
                }
                if (event.key.code == keyBinds[Actions::UP]) {
                    updatePlayerPosition(vf2d{0, -5});
                }
                if (event.key.code == keyBinds[Actions::DOWN]) {
                    updatePlayerPosition(vf2d{0, 5});
                }
                if (event.key.code == keyBinds[Actions::LEFT]) {
                    updatePlayerPosition(vf2d{-5, 0});
                }
                if (event.key.code == keyBinds[Actions::RIGHT]) {
                    updatePlayerPosition(vf2d{5, 0});
                }
                if (event.key.code == keyBinds[Actions::PAUSE]) {
                    this->setScene(Scenes::Scene::IN_GAME_MENU);
                }
            }
        }
        if (c.IsConnected()) {
            // std::cout << "Connected to Server" << std::endl;
            // /////////////////////////////////////
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
                    c.addEntity(entity, componentManager, textureManager);
                } break;
                case TypeMessage::CreateEntityResponse: {
                } break;
                case TypeMessage::DestroyEntityMessage: {
                    r_type::net::Message<TypeMessage> reponse;
                    uint32_t id;
                    msg >> id;
                    if (id == c.getPlayerId()) {
                        death();
                    }
                    c.removeEntity(id, componentManager);
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
                case TypeMessage::FinishInitialization: {
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
        pos.value()->x = 960;
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
        pos.value()->x = 960;
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
        pos.value()->x = 960;
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

void createDaltonismChoiceButtons(std::vector<Entity *> *buttons,
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
        pos.value()->x = 1460;
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
        pos.value()->x = 1460;
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
        pos.value()->x = 1460;
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
        pos.value()->x = 1460;
        pos.value()->y = 550;
    }

    buttons->push_back(&normalButton);
    buttons->push_back(&tritanopiaButton);
    buttons->push_back(&deuteranopiaButton);
    buttons->push_back(&protanopiaButton);
}

void createGameModeChoiceButtons(std::vector<Entity *> *buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> easyButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::EASY);
        return currentScene;
    };
    Entity easyButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Easy", &easyButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(easyButton.getId());
    if (pos) {
        pos.value()->x = 1460;
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
        pos.value()->x = 1460;
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
        pos.value()->x = 1460;
        pos.value()->y = 550;
    }

    buttons->push_back(&easyButton);
    buttons->push_back(&mediumButton);
    buttons->push_back(&hardButton);
}

sf::Keyboard::Key waitForKey(sf::RenderWindow *_window)
{
    std::cout << "Waiting for key" << std::endl;
    sf::Event event;
    while (true) {
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                return event.key.code;
            }
        }
    }
}

void createKeyBindingButtons(std::vector<Entity *> *buttons, ComponentManager &componentManager,
    EntityManager &entityManager, TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *, Scenes::Actions)> bindkey = [](Scenes *currentScene,
                                                                     Scenes::Actions action) {
        sf::Keyboard::Key key = waitForKey(currentScene->getRenderWindow());
        currentScene->keyBinds[action] = key;
        std::cout << currentScene->keyBinds[action] << "ton pere" << std::endl;
        return currentScene;
    };

    Entity bindUpButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Up : ", &bindkey);
    auto pos = componentManager.getComponent<PositionComponent>(bindUpButton.getId());
    if (pos) {
        pos.value()->x = 1650;
        pos.value()->y = 100;
    }

    Entity bindDownButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Down : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindDownButton.getId());
    if (pos) {
        pos.value()->x = 1650;
        pos.value()->y = 250;
    }

    Entity bindLeftButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Left : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindLeftButton.getId());
    if (pos) {
        pos.value()->x = 1400;
        pos.value()->y = 250;
    }

    Entity bindRightButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Right : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindRightButton.getId());
    if (pos) {
        pos.value()->x = 1900;
        pos.value()->y = 250;
    }

    Entity bindFireButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Fire : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindFireButton.getId());
    if (pos) {
        pos.value()->x = 1650;
        pos.value()->y = 400;
    }

    Entity bindPauseButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Pause : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindPauseButton.getId());
    if (pos) {
        pos.value()->x = 1650;
        pos.value()->y = 550;
    }

    // Entity bindPauseButton = entityFactory.createSmallButton(
    //     entityManager, componentManager, textureManager, "Pause : ", &bindkey);
    // pos = componentManager.getComponent<PositionComponent>(bindPauseButton.getId());
    // if (pos) {
    //     pos.value()->x = 1560;
    //     pos.value()->y = 750;
    // }

    Entity bindQuitButton = entityFactory.createSmallButton(
        entityManager, componentManager, textureManager, "Quit : ", &bindkey);
    pos = componentManager.getComponent<PositionComponent>(bindQuitButton.getId());
    if (pos) {
        pos.value()->x = 1650;
        pos.value()->y = 700;
    }

    buttons->push_back(&bindUpButton);
    buttons->push_back(&bindDownButton);
    buttons->push_back(&bindLeftButton);
    buttons->push_back(&bindRightButton);
    buttons->push_back(&bindFireButton);
    buttons->push_back(&bindPauseButton);
    buttons->push_back(&bindQuitButton);
}

/**
 * @brief Displays the settings menu.
 *
 * This function is responsible for displaying the settings menu in the game.
 * It does not return any value.
 */
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
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale);
    componentManager.addComponent<SpriteComponent>(background.getId(), spriteComponent);

    // Create the buttons
    std::function<Scenes *(Scenes *)> onDaltonismModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayDaltonismChoice = !currentScene->displayDaltonismChoice;
        currentScene->displayGameModeChoice = false;
        currentScene->displayKeyBinds = false;
        currentScene->settingsMenu();
        return currentScene;
    };
    Entity daltonismModeButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Daltonism Mode", &onDaltonismModeButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(daltonismModeButton.getId());
    if (pos) {
        pos.value()->x = 960;
        pos.value()->y = 100;
    }

    std::function<Scenes *(Scenes *)> onGameModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayGameModeChoice = !currentScene->displayGameModeChoice;
        currentScene->displayDaltonismChoice = false;
        currentScene->displayKeyBinds = false;
        currentScene->settingsMenu();
        return currentScene;
    };
    Entity gameModeButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Game Mode", &onGameModeButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(gameModeButton.getId());
    if (pos) {
        pos.value()->x = 960;
        pos.value()->y = 250;
    }

    std::function<Scenes *(Scenes *)> onKeybindButtonClicked = [](Scenes *currentScene) {
        currentScene->displayKeyBinds = !currentScene->displayKeyBinds;
        currentScene->displayDaltonismChoice = false;
        currentScene->displayGameModeChoice = false;
        currentScene->settingsMenu();
        return currentScene;
    };
    Entity keyBindsButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Key Binds", &onKeybindButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(keyBindsButton.getId());
    if (pos) {
        pos.value()->x = 960;
        pos.value()->y = 400;
    }

    std::function<Scenes *(Scenes *)> onBackButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(currentScene->getPreviousScene());
        return currentScene;
    };
    Entity backButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Back", &onBackButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(backButton.getId());
    if (pos) {
        pos.value()->x = 960;
        pos.value()->y = 650;
    }

    buttons.push_back(&daltonismModeButton);
    buttons.push_back(&gameModeButton);
    buttons.push_back(&keyBindsButton);
    buttons.push_back(&backButton);

    if (displayDaltonismChoice) {
        // createDaltonismChoiceButtons(
        //     &buttons, componentManager, entityManager, textureManager, entityFactory);
    }
    if (displayGameModeChoice) {
        // createGameModeChoiceButtons(
        //     &buttons, componentManager, entityManager, textureManager, entityFactory);
    }
    if (displayKeyBinds) {
        // createKeyBindingButtons(
        //     &buttons, componentManager, entityManager, textureManager, entityFactory);
    }

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::SETTINGS_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(componentManager);
    }
}

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
