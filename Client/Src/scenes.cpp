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
#include <Systems/system_manager.hpp>
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

/**
 * @brief Handles events for the scene, including window close and mouse button press events.
 *
 * This function processes events from the given RenderWindow and performs actions based on the
 * type of event. It handles window close events and mouse button press events. For mouse button
 * press events, it checks if the left mouse button was pressed and if the click occurred within
 * the bounds of any button entities. If a button is clicked, it triggers the associated
 * OnClickComponent or BindComponent actions.
 *
 * @param event The event to handle.
 * @param componentManager Reference to the ComponentManager to access components of entities.
 * @param _window Pointer to the RenderWindow where events are polled from.
 * @param buttons Vector of shared pointers to Entity objects representing buttons.
 */
void handleEvents(sf::Event event, ComponentManager &componentManager, sf::RenderWindow *_window,
    std::vector<std::shared_ptr<Entity>> buttons, Scenes *scenes)
{
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            auto pos = sf::Mouse::getPosition(*_window);
            for (auto button : buttons) {
                auto posComp =
                    componentManager.getComponent<PositionComponent>(button.get()->getId());
                auto sprite =
                    componentManager.getComponent<SpriteComponent>(button.get()->getId());
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
    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;
    EntityFactory entityFactory;

    SystemManager systemManager;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(*_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(*_window, componentManager);

    systemManager.addSystem(updateSystem);
    systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, 0);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create buttons
    std::function<Scenes *(Scenes *)> onPlayButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };

    std::shared_ptr<Entity> playButton = std::make_shared<Entity>(entityFactory.createButton(
        entityManager, componentManager, textureManager, "Play", &onPlayButtonClicked, 960, 100));

    std::function<Scenes *(Scenes *)> onSettingsButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::SETTINGS_MENU);
        return currentScene;
    };
    std::shared_ptr<Entity> settingsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Settings", &onSettingsButtonClicked, 960, 250));

    std::function<Scenes *(Scenes *)> onQuitButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::EXIT);
        return currentScene;
    };

    std::shared_ptr<Entity> quitButton = std::make_shared<Entity>(entityFactory.createButton(
        entityManager, componentManager, textureManager, "Quit", &onQuitButtonClicked, 960, 500));

    buttons.push_back(playButton);
    buttons.push_back(settingsButton);
    buttons.push_back(quitButton);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::MAIN_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        systemManager.updateSystems(deltaTime);
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

/**
 * @brief Displays the in-game menu.
 *
 */
void Scenes::inGameMenu()
{
    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;
    EntityFactory entityFactory;

    SystemManager systemManager;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(*_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(*_window, componentManager);

    systemManager.addSystem(updateSystem);
    systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, 0);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create the buttons
    std::function<Scenes *(Scenes *)> onResumeButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };
    std::shared_ptr<Entity> resumeButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Resume", &onResumeButtonClicked, 960, 100));

    std::function<Scenes *(Scenes *)> onSettingsButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::SETTINGS_MENU);
        return currentScene;
    };
    std::shared_ptr<Entity> settingsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Settings", &onSettingsButtonClicked, 960, 250));

    std::function<Scenes *(Scenes *)> onReturnToMainMenuButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::MAIN_MENU);
        return currentScene;
    };
    std::shared_ptr<Entity> returnToMainMenu =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Return To Main Menu", &onReturnToMainMenuButtonClicked, 960, 500));

    buttons.push_back(resumeButton);
    buttons.push_back(settingsButton);
    buttons.push_back(returnToMainMenu);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::IN_GAME_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        systemManager.updateSystems(deltaTime);
    }
}

void createDaltonismChoiceButtons(std::vector<std::shared_ptr<Entity>> &buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> onNormalButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::NORMAL);
        return currentScene;
    };
    std::shared_ptr<Entity> normalButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Normal", &onNormalButtonClicked, 1460, 100));

    std::function<Scenes *(Scenes *)> onTritanopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::TRITANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> tritanopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Tritanopia", &onTritanopiaButtonClicked, 1460, 250));

    std::function<Scenes *(Scenes *)> onDeuteranopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::DEUTERANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> deuteranopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Deuteranopia", &onDeuteranopiaButtonClicked, 1460, 400));

    std::function<Scenes *(Scenes *)> onProtanopiaButtonClicked = [](Scenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::PROTANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> protanopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Protanopia", &onProtanopiaButtonClicked, 1460, 550));

    buttons.push_back(normalButton);
    buttons.push_back(tritanopiaButton);
    buttons.push_back(deuteranopiaButton);
    buttons.push_back(protanopiaButton);
}

void createGameModeChoiceButtons(std::vector<std::shared_ptr<Entity>> &buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> easyButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::EASY);
        return currentScene;
    };
    std::shared_ptr<Entity> easyButton = std::make_shared<Entity>(entityFactory.createButton(
        entityManager, componentManager, textureManager, "Easy", &easyButtonClicked, 1460, 250));

    std::function<Scenes *(Scenes *)> mediumButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::MEDIUM);
        return currentScene;
    };
    std::shared_ptr<Entity> mediumButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Medium", &mediumButtonClicked, 1460, 400));

    std::function<Scenes *(Scenes *)> hardButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::HARD);
        return currentScene;
    };
    std::shared_ptr<Entity> hardButton = std::make_shared<Entity>(entityFactory.createButton(
        entityManager, componentManager, textureManager, "Hard", &hardButtonClicked, 1460, 550));

    buttons.push_back(easyButton);
    buttons.push_back(mediumButton);
    buttons.push_back(hardButton);
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

void createKeyBindingButtons(std::vector<std::shared_ptr<Entity>> &buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *, Scenes::Actions)> bindKey = [](Scenes *currentScene,
                                                                     Scenes::Actions action) {
        sf::Keyboard::Key key = waitForKey(currentScene->getRenderWindow());
        currentScene->keyBinds[action] = key;
        std::cout << currentScene->keyBinds[action] << "ok" << std::endl;
        return currentScene;
    };

    std::shared_ptr<Entity> bindUpButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Up : ", &bindKey, 1650, 100));

    std::shared_ptr<Entity> bindDownButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Down : ", &bindKey, 1650, 250));

    std::shared_ptr<Entity> bindLeftButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Left : ", &bindKey, 1400, 250));

    std::shared_ptr<Entity> bindRightButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Right : ", &bindKey, 1900, 250));

    std::shared_ptr<Entity> bindFireButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Fire : ", &bindKey, 1650, 400));

    std::shared_ptr<Entity> bindPauseButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Pause : ", &bindKey, 1650, 550));

    // Entity bindPauseButton = entityFactory.createSmallButton(
    //     entityManager, componentManager, textureManager, "Pause : ", &bindKey);
    // pos = componentManager.getComponent<PositionComponent>(bindPauseButton.get()->getId());
    // if (pos) {
    //     pos.value()->x = 1560;
    //     pos.value()->y = 750;
    // }

    std::shared_ptr<Entity> bindQuitButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(
            entityManager, componentManager, textureManager, "Quit : ", &bindKey, 1650, 700));

    buttons.push_back(bindUpButton);
    buttons.push_back(bindDownButton);
    buttons.push_back(bindLeftButton);
    buttons.push_back(bindRightButton);
    buttons.push_back(bindFireButton);
    buttons.push_back(bindPauseButton);
    buttons.push_back(bindQuitButton);
}

/**
 * @brief Displays the settings menu.
 *
 * This function is responsible for displaying the settings menu in the game.
 * It does not return any value.
 */
void Scenes::settingsMenu()
{
    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;
    EntityFactory entityFactory;

    SystemManager systemManager;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(*_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(*_window, componentManager);

    systemManager.addSystem(updateSystem);
    systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, 0);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create the buttons
    std::function<Scenes *(Scenes *)> onDaltonismModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayDaltonismChoice = !currentScene->displayDaltonismChoice;
        currentScene->displayGameModeChoice = false;
        currentScene->displayKeyBinds = false;
        currentScene->settingsMenu();
        return currentScene;
    };

    std::shared_ptr<Entity> daltonismModeButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Daltonism Mode", &onDaltonismModeButtonClicked, 960, 100));

    std::function<Scenes *(Scenes *)> onGameModeButtonClicked = [](Scenes *currentScene) {
        currentScene->displayGameModeChoice = !currentScene->displayGameModeChoice;
        currentScene->displayDaltonismChoice = false;
        currentScene->displayKeyBinds = false;
        currentScene->settingsMenu();
        return currentScene;
    };

    std::shared_ptr<Entity> gameModeButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Game Mode", &onGameModeButtonClicked, 960, 250));

    std::function<Scenes *(Scenes *)> onKeyBindButtonClicked = [](Scenes *currentScene) {
        currentScene->displayKeyBinds = !currentScene->displayKeyBinds;
        currentScene->displayDaltonismChoice = false;
        currentScene->displayGameModeChoice = false;
        currentScene->settingsMenu();
        return currentScene;
    };

    std::shared_ptr<Entity> keyBindsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, "Key Binds", &onKeyBindButtonClicked, 960, 400));

    std::function<Scenes *(Scenes *)> onBackButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(currentScene->getPreviousScene());
        return currentScene;
    };
    std::shared_ptr<Entity> backButton = std::make_shared<Entity>(entityFactory.createButton(
        entityManager, componentManager, textureManager, "Back", &onBackButtonClicked, 960, 650));

    buttons.push_back(daltonismModeButton);
    buttons.push_back(gameModeButton);
    buttons.push_back(keyBindsButton);
    buttons.push_back(backButton);

    if (displayDaltonismChoice) {
        // createDaltonismChoiceButtons(
        //     &buttons, componentManager, entityManager, textureManager, entityFactory);
        sf::RectangleShape filter(sf::Vector2f((*_window).getSize().x, (*_window).getSize().y));
        currentDaltonismMode = DaltonismMode::TRITANOPIA;
        switch (currentDaltonismMode) {
        case DaltonismMode::NORMAL:
            filter.setFillColor(sf::Color(0, 0, 0, 0));
            break;
        case DaltonismMode::TRITANOPIA:
            filter.setFillColor(sf::Color(255, 255, 100, 100));
            break;
        case DaltonismMode::DEUTERANOPIA:
            filter.setFillColor(sf::Color(255, 100, 255, 100));
            break;
        case DaltonismMode::PROTANOPIA:
            filter.setFillColor(sf::Color(255, 255, 100, 100));
            break;
        }
    }

    if (displayGameModeChoice) {
        // createGameModeChoiceButtons(
        //     &buttons, componentManager, entityManager, textureManager, entityFactory);
    }
    if (displayKeyBinds) {
        // createKeyBindingButtons(buttons, componentManager, entityManager, textureManager,
        // entityFactory);
    }

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::SETTINGS_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        systemManager.updateSystems(deltaTime);
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

void Scenes::gameLoop()
{
    r_type::net::Client c;
    c.Connect("127.0.0.1", 60000);

    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SystemManager systemManager;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(*_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(*_window, componentManager);

    systemManager.addSystem(updateSystem);
    systemManager.addSystem(renderSystem);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Event event;

    sf::Clock clock; ///////////////////////////////////////////////////// TEMPORARY

    auto updatePlayerPosition = [&](const vf2d &delta) {
        r_type::net::Message<TypeMessage> msg;
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
        float deltaTime = clock.restart().asSeconds();
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
                    r_type::net::Message<TypeMessage> response;
                    uint32_t id;
                    msg >> id;
                    if (id == c.getPlayerId()) {
                        death();
                    }
                    c.removeEntity(id, componentManager);
                    c.removeEntity(id, componentManager);
                    response.header.id = TypeMessage::DestroyEntityResponse;
                    c.Send(response);
                } break;
                case TypeMessage::UpdateEntity: {
                    r_type::net::Message<TypeMessage> response;
                    response.header.id = TypeMessage::UpdateEntityResponse;
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

        systemManager.updateSystems(deltaTime);
    }
}
