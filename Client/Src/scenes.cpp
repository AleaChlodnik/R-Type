/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#include <Components/components.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Net/client.hpp>
#include <Systems/systems.hpp>
#include <audio_manager.hpp>
#include <chrono>
#include <creatable_client_object.hpp>
#include <font_manager.hpp>
#include <functional>
#include <iostream>
#include <scenes.hpp>
#include <sound_path.hpp>
#include <texture_manager.hpp>

Scenes::Scenes(std::string ip, int port) : IScenes(), AScenes(ip, port)
{
    _window.create(sf::VideoMode::getDesktopMode(), "R-Type");
    _window.setFramerateLimit(60);
}

void reloadFilter(sf::RectangleShape &rectangle, AScenes::DaltonismMode mode)
{
    if (rectangle.getSize().x == 0 && rectangle.getSize().y == 0) {
        std::cout << "no RectangleShapeComponent found." << std::endl;
        return;
    }
    switch (mode) {
    case AScenes::DaltonismMode::PROTANOPIA:
        rectangle.setFillColor(sf::Color(255, 153, 102, 100));
        break;
    case AScenes::DaltonismMode::DEUTERANOPIA:
        rectangle.setFillColor(sf::Color(102, 153, 255, 100));
        break;
    case AScenes::DaltonismMode::TRITANOPIA:
        rectangle.setFillColor(sf::Color(255, 204, 255, 100));
        break;
    default:
        rectangle.setFillColor(sf::Color(255, 255, 255, 0));
        break;
    }
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
        if (event.type == sf::Event::Closed) {
            _window->close();
        }
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
                                        bind.value()->bind(scenes, Scenes::Actions(index - 4));
                                        auto text = componentManager.getComponent<TextComponent>(
                                            button->getId());
                                        if (text) {
                                            std::string str = text.value()->text.getString();
                                            str = str.substr(0, str.find(":") + 1) + " " +
                                                keyToString(
                                                    scenes->keyBinds[AScenes::Actions(index - 4)]);
                                            text.value()->text.setString(str);
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
    FontManager fontManager;
    EntityFactory entityFactory;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(_window, componentManager);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, AScenes::SpriteType::BACKGROUND);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create filter
    this->filter = std::make_shared<Entity>(
        entityFactory.createFilter(entityManager, componentManager, _currentDaltonismMode));

    // Create buttons
    std::function<IScenes *(AScenes *)> onPlayButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };

    std::shared_ptr<Entity> playButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Play", &onPlayButtonClicked, 960, 100));

    std::function<IScenes *(AScenes *)> onSettingsButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(Scenes::Scene::SETTINGS_MENU);
        return currentScene;
    };
    std::shared_ptr<Entity> settingsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Settings", &onSettingsButtonClicked, 960, 250));

    std::function<IScenes *(AScenes *)> onQuitButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(Scenes::Scene::EXIT);
        return currentScene;
    };

    std::shared_ptr<Entity> quitButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Quit", &onQuitButtonClicked, 960, 500));

    buttons.push_back(playButton);
    buttons.push_back(settingsButton);
    buttons.push_back(quitButton);

    sf::Clock clock;
    sf::Event event;

    while (_window.isOpen() && this->_currentScene == Scenes::Scene::MAIN_MENU) {

        handleEvents(event, componentManager, &_window, buttons, this);

        updateSystem->updateSpritePositions(componentManager, entityManager);
        renderSystem->render(componentManager);
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
    FontManager fontManager;
    EntityFactory entityFactory;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(_window, componentManager);

    // systemManager.addSystem(updateSystem);
    // systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, AScenes::SpriteType::BACKGROUND);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create filter
    this->filter = std::make_shared<Entity>(
        entityFactory.createFilter(entityManager, componentManager, _currentDaltonismMode));

    // Create the buttons
    std::function<IScenes *(AScenes *)> onResumeButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(Scenes::Scene::GAME_LOOP);
        return currentScene;
    };
    std::shared_ptr<Entity> resumeButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Resume", &onResumeButtonClicked, 960, 100));

    std::function<IScenes *(AScenes *)> onSettingsButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(Scenes::Scene::SETTINGS_MENU);
        return currentScene;
    };
    std::shared_ptr<Entity> settingsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Settings", &onSettingsButtonClicked, 960, 250));

    std::function<IScenes *(AScenes *)> onReturnToMainMenuButtonClicked =
        [](AScenes *currentScene) {
            currentScene->setScene(Scenes::Scene::MAIN_MENU);
            return currentScene;
        };
    std::shared_ptr<Entity> returnToMainMenu = std::make_shared<Entity>(
        entityFactory.createButton(entityManager, componentManager, textureManager, fontManager,
            "Return To Main Menu", &onReturnToMainMenuButtonClicked, 960, 500));

    buttons.push_back(resumeButton);
    buttons.push_back(settingsButton);
    buttons.push_back(returnToMainMenu);

    sf::Clock clock;
    sf::Event event;

    while (_window.isOpen() && this->_currentScene == Scenes::Scene::IN_GAME_MENU) {

        handleEvents(event, componentManager, &_window, buttons, this);

        updateSystem->updateSpritePositions(componentManager, entityManager);
        renderSystem->render(componentManager);
    }
}

void createDaltonismChoiceButtons(std::vector<std::shared_ptr<Entity>> &buttons,
    ComponentManager &componentManager, EntityManager &entityManager,
    TextureManager &textureManager, FontManager fontManager, EntityFactory &entityFactory)
{
    std::function<IScenes *(AScenes *)> onNormalButtonClicked = [&](AScenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::NORMAL);
        ;
        auto filter =
            componentManager.getComponent<RectangleShapeComponent>(currentScene->filter->getId());
        reloadFilter(filter.value()->rectangleShape, AScenes::DaltonismMode::NORMAL);
        return currentScene;
    };
    std::shared_ptr<Entity> normalButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Normal", &onNormalButtonClicked, 1460, 100));

    std::function<IScenes *(AScenes *)> onTritanopiaButtonClicked = [&](AScenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::TRITANOPIA);
        auto filter =
            componentManager.getComponent<RectangleShapeComponent>(currentScene->filter->getId());
        reloadFilter(filter.value()->rectangleShape, AScenes::DaltonismMode::TRITANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> tritanopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Tritanopia", &onTritanopiaButtonClicked, 1460, 250));

    std::function<IScenes *(AScenes *)> onDeuteranopiaButtonClicked = [&](AScenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::DEUTERANOPIA);
        auto filter =
            componentManager.getComponent<RectangleShapeComponent>(currentScene->filter->getId());
        reloadFilter(filter.value()->rectangleShape, AScenes::DaltonismMode::DEUTERANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> deuteranopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Deuteranopia", &onDeuteranopiaButtonClicked, 1460, 400));

    std::function<IScenes *(AScenes *)> onProtanopiaButtonClicked = [&](AScenes *currentScene) {
        currentScene->setDaltonism(Scenes::DaltonismMode::PROTANOPIA);
        auto filter =
            componentManager.getComponent<RectangleShapeComponent>(currentScene->filter->getId());
        reloadFilter(filter.value()->rectangleShape, AScenes::DaltonismMode::PROTANOPIA);
        return currentScene;
    };
    std::shared_ptr<Entity> protanopiaButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Protanopia", &onProtanopiaButtonClicked, 1460, 550));

    buttons.push_back(normalButton);
    buttons.push_back(tritanopiaButton);
    buttons.push_back(deuteranopiaButton);
    buttons.push_back(protanopiaButton);
}

sf::Keyboard::Key waitForKey(sf::RenderWindow *_window)
{
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
    TextureManager &textureManager, FontManager fontManager, EntityFactory &entityFactory,
    std::map<Scenes::Actions, sf::Keyboard::Key> &keyBinds)
{
    std::function<IScenes *(AScenes *, AScenes::Actions)> bindKey = [](AScenes *currentScene,
                                                                        AScenes::Actions action) {
        sf::Keyboard::Key key = waitForKey(currentScene->getRenderWindow());
        currentScene->keyBinds[action] = key;
        return currentScene;
    };

    std::shared_ptr<Entity> bindUpButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Up: " + keyToString(keyBinds[Scenes::Actions::UP]),
            &bindKey, 1550, 100));

    std::shared_ptr<Entity> bindDownButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Down: " + keyToString(keyBinds[Scenes::Actions::DOWN]),
            &bindKey, 1550, 250));

    std::shared_ptr<Entity> bindLeftButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Left: " + keyToString(keyBinds[Scenes::Actions::LEFT]),
            &bindKey, 1300, 250));

    std::shared_ptr<Entity> bindRightButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Right: " + keyToString(keyBinds[Scenes::Actions::RIGHT]),
            &bindKey, 1800, 250));

    std::shared_ptr<Entity> bindFireButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Fire: " + keyToString(keyBinds[Scenes::Actions::FIRE]),
            &bindKey, 1550, 400));

    std::shared_ptr<Entity> bindPauseButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Pause: " + keyToString(keyBinds[Scenes::Actions::PAUSE]),
            &bindKey, 1550, 550));

    std::shared_ptr<Entity> bindQuitButton =
        std::make_shared<Entity>(entityFactory.createSmallButton(entityManager, componentManager,
            textureManager, fontManager, "Quit: " + keyToString(keyBinds[Scenes::Actions::QUIT]),
            &bindKey, 1550, 700));

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
    FontManager fontManager;
    EntityFactory entityFactory;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(_window, componentManager);

    // systemManager.addSystem(updateSystem);
    // systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, AScenes::SpriteType::BACKGROUND);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create filter
    this->filter = std::make_shared<Entity>(
        entityFactory.createFilter(entityManager, componentManager, _currentDaltonismMode));

    // Create the buttons
    std::function<IScenes *(AScenes *)> onDaltonismModeButtonClicked = [](AScenes *currentScene) {
        currentScene->setDisplayDaltonismChoice(!currentScene->getDisplayDaltonismChoice());
        currentScene->setDisplayKeyBindsChoice(false);
        currentScene->settingsMenu();
        return currentScene;
    };

    std::shared_ptr<Entity> daltonismModeButton = std::make_shared<Entity>(
        entityFactory.createButton(entityManager, componentManager, textureManager, fontManager,
            "Daltonism Mode", &onDaltonismModeButtonClicked, 960, 250));

    std::function<IScenes *(AScenes *)> onKeyBindButtonClicked = [](AScenes *currentScene) {
        currentScene->setDisplayKeyBindsChoice(!currentScene->getDisplayKeyBindsChoice());
        currentScene->setDisplayDaltonismChoice(false);
        currentScene->settingsMenu();
        return currentScene;
    };

    std::shared_ptr<Entity> keyBindsButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Key Binds", &onKeyBindButtonClicked, 960, 400));

    std::function<IScenes *(AScenes *)> onBackButtonClicked = [](AScenes *currentScene) {
        currentScene->setScene(currentScene->getPreviousScene());
        return currentScene;
    };
    std::shared_ptr<Entity> backButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Back", &onBackButtonClicked, 960, 650));

    buttons.push_back(daltonismModeButton);
    buttons.push_back(keyBindsButton);
    buttons.push_back(backButton);

    if (_displayDaltonismChoice) {
        createDaltonismChoiceButtons(
            buttons, componentManager, entityManager, textureManager, fontManager, entityFactory);
    }

    if (_displayKeyBindsChoice) {
        createKeyBindingButtons(buttons, componentManager, entityManager, textureManager,
            fontManager, entityFactory, keyBinds);
    }

    sf::Clock clock;
    sf::Event event;

    while (_window.isOpen() && this->_currentScene == Scenes::Scene::SETTINGS_MENU) {

        handleEvents(event, componentManager, &_window, buttons, this);

        updateSystem->updateSpritePositions(componentManager, entityManager);
        renderSystem->render(componentManager);
    }
}

void Scenes::difficultyChoices()
{
    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;
    FontManager fontManager;
    EntityFactory entityFactory;

    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(_window, componentManager);

    // systemManager.addSystem(updateSystem);
    // systemManager.addSystem(renderSystem);

    buttons = {};

    // Create background
    std::shared_ptr<Entity> background =
        std::make_shared<Entity>(entityFactory.createBackground(entityManager, componentManager));
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, AScenes::SpriteType::BACKGROUND);
    componentManager.addComponent<SpriteComponent>(background.get()->getId(), spriteComponent);

    // Create filter
    this->filter = std::make_shared<Entity>(
        entityFactory.createFilter(entityManager, componentManager, _currentDaltonismMode));

    std::function<IScenes *(AScenes *)> easyButtonClicked = [](AScenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::EASY);
        return currentScene;
    };
    std::shared_ptr<Entity> easyButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Easy", &easyButtonClicked, 1460, 250));

    std::function<IScenes *(AScenes *)> mediumButtonClicked = [](AScenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::MEDIUM);
        return currentScene;
    };
    std::shared_ptr<Entity> mediumButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Medium", &mediumButtonClicked, 1460, 400));

    std::function<IScenes *(AScenes *)> hardButtonClicked = [](AScenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::HARD);
        return currentScene;
    };
    std::shared_ptr<Entity> hardButton =
        std::make_shared<Entity>(entityFactory.createButton(entityManager, componentManager,
            textureManager, fontManager, "Hard", &hardButtonClicked, 1460, 550));

    buttons.push_back(easyButton);
    buttons.push_back(mediumButton);
    buttons.push_back(hardButton);
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
    switch (this->_currentScene) {
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
    _networkClient.Connect(_ip, _port);

    EntityManager entityManager;
    ComponentManager componentManager;
    TextureManager textureManager;
    auto audioManager = std::make_shared<AudioManager>();

    std::shared_ptr<AudioSystem> audioSystem = std::make_shared<AudioSystem>(audioManager);
    std::shared_ptr<UpdateSystem> updateSystem =
        std::make_shared<UpdateSystem>(_window, componentManager, entityManager);
    std::shared_ptr<RenderSystem> renderSystem =
        std::make_shared<RenderSystem>(_window, componentManager);

    sf::Event event;
    sf::Clock clock;

    const int FIRE_COOLDOWN_MS = 500;
    std::chrono::steady_clock::time_point lastFireTime = std::chrono::steady_clock::now();

    auto pixelToPercent = [&](float v1, float v2) { return (v1 / v2) * 100; };

    auto movePlayer = [&](const vf2d &delta, sf::Vector2u windowSize) {
        r_type::net::Message<TypeMessage> msg;
        vf2d requestedPosition;
        msg.header.id = TypeMessage::MoveEntityMessage;
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto spriteComponent = sprites[_networkClient.getPlayerId()];
            auto playerSprite = std::any_cast<SpriteComponent>(&spriteComponent);
            requestedPosition.x =
                pixelToPercent(playerSprite->sprite.getPosition().x, windowSize.x) + delta.x;
            requestedPosition.y =
                pixelToPercent(playerSprite->sprite.getPosition().y, windowSize.y) + delta.y;
            msg << requestedPosition;
            _networkClient.Send(msg);
        }
    };

    auto fireMissile = [&]() {
        auto currentTime = std::chrono::steady_clock::now();
        auto timeSinceLastFire =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFireTime)
                .count();
        if (timeSinceLastFire >= FIRE_COOLDOWN_MS) {
            r_type::net::Message<TypeMessage> msg;
            msg.header.id = TypeMessage::CreateEntityMessage;
            msg << CreatableClientObject::PLAYERMISSILE;
            _networkClient.Send(msg);
            lastFireTime = currentTime;
            audioSystem->playSoundEffect(SoundFactory(ActionType::Shot));
        }
    };

    sf::Vector2u windowSize = _window.getSize();

    audioSystem->playBackgroundMusic(SoundFactory(ActionType::Background));
    // audioSystem->playBackgroundMusic(""); // Test with quentins sound

    while (_window.isOpen()) {
        // float deltaTime = clock.restart().asSeconds();
        while (_window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                StopGameLoop(audioSystem);
            }
            if (sf::Keyboard::isKeyPressed(keyBinds[Actions::FIRE])) {
                fireMissile();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    _networkClient.PingServer();
                }
                if (event.key.code == sf::Keyboard::V) {
                    _networkClient.MessageAll();
                }
                if (event.key.code == keyBinds[Actions::FIRE]) {
                    fireMissile();
                }
                if (event.key.code == keyBinds[Actions::QUIT]) {
                    StopGameLoop(audioSystem);
                }
                if (event.key.code == keyBinds[Actions::UP]) {
                    movePlayer(vf2d{0, -1}, windowSize);
                }
                if (event.key.code == keyBinds[Actions::DOWN]) {
                    movePlayer(vf2d{0, 1}, windowSize);
                }
                if (event.key.code == keyBinds[Actions::LEFT]) {
                    movePlayer(vf2d{-1, 0}, windowSize);
                }
                if (event.key.code == keyBinds[Actions::RIGHT]) {
                    movePlayer(vf2d{1, 0}, windowSize);
                }
                if (event.key.code == keyBinds[Actions::PAUSE]) {
                    this->setScene(Scenes::Scene::IN_GAME_MENU);
                }
            }
        }

        if (_networkClient.IsConnected()) {
            // std::cout << "Connected to Server" << std::endl;
            while (!_networkClient.Incoming().empty()) {
                auto msg = _networkClient.Incoming().pop_front().msg;
                HandleMessage(msg, componentManager, textureManager, windowSize, audioSystem);
            }
        } else {
            std::cout << "Server Down" << std::endl;
            _window.close();
        }
        // updateSystem->updateSpritePositions(componentManager, entityManager);

        std::thread displayUpdate(
            [this, updateSystem, renderSystem, &componentManager, &entityManager]() {
                updateSystem->updateSpritePositions(componentManager, entityManager);
            });

        displayUpdate.join();
        renderSystem->render(componentManager);
    }
}

void Scenes::HandleMessage(r_type::net::Message<TypeMessage> &msg,
    ComponentManager &componentManager, TextureManager &textureManager,
    const sf::Vector2u &windowSize, std::shared_ptr<AudioSystem> &audioSystem)
{
    switch (msg.header.id) {
    case TypeMessage::ServerAccept: {
        std::cout << "Server Accepted Connection" << std::endl;
        r_type::net::Message<TypeMessage> response;
        response.header.id = TypeMessage::SendPlayer;
        _networkClient.Send(response);
    } break;
    case TypeMessage::ServerPing: {
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point timeThen;
        msg >> timeThen;
        std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count()
                  << std::endl;
    } break;
    case TypeMessage::ServerMessage: {
        uint32_t clientID;
        msg >> clientID;
        std::cout << "Hello from [" << clientID << "]" << std::endl;
    } break;
    case TypeMessage::SendPlayerInformation: {
        EntityInformation entity;
        r_type::net::Message<TypeMessage> response;
        response.header.id = TypeMessage::ReceivePlayerInformation;
        _networkClient.Send(response);
        msg >> entity;
        _networkClient.setPlayerId(entity.uniqueID);
        _networkClient.addEntity(entity, componentManager, textureManager, windowSize);
    } break;
    case TypeMessage::ServerDeny: {
        std::cout << "Server Denied Connection" << std::endl;
    } break;
    case TypeMessage::MessageAll: {
    } break;
    case TypeMessage::ClientConnect: {
    } break;
    case TypeMessage::CreateEntityMessage: {
        EntityInformation entity;
        r_type::net::Message<TypeMessage> response;
        response.header.id = TypeMessage::CreateEntityResponse;
        _networkClient.Send(response);
        msg >> entity;
        _networkClient.addEntity(entity, componentManager, textureManager, windowSize);
    } break;
    case TypeMessage::DestroyEntityMessage: {
        r_type::net::Message<TypeMessage> response;
        uint32_t id;
        msg >> id;
        audioSystem->playSoundEffect(SoundFactory(ActionType::Explosion));
        if (id == _networkClient.getPlayerId()) {
            StopGameLoop(audioSystem);
        }
        _networkClient.removeEntity(id, componentManager);
        response.header.id = TypeMessage::DestroyEntityResponse;
        _networkClient.Send(response);
    } break;
    case TypeMessage::UpdateEntity: {
    } break;
    case TypeMessage::UpdateEntityResponse: {
    } break;
    case TypeMessage::MoveEntityMessage: {
        r_type::net::Message<TypeMessage> response;
        response.header.id = TypeMessage::MoveEntityResponse;
        EntityInformation entity;
        msg >> entity;
        _networkClient.moveEntity(entity, componentManager, windowSize, textureManager);
    } break;
    case TypeMessage::MoveEntityResponse: {
    } break;
    case TypeMessage::DestroyEntityResponse: {
    } break;
    case TypeMessage::FinishInitialization: {
    } break;
    case TypeMessage::AnimateEntityMessage: {
        r_type::net::Message<TypeMessage> response;
        uint32_t id;
        AnimationComponent rect({0, 0}, {0, 0});
        msg >> rect.offset >> rect.dimension >> id;
        _networkClient.animateEntity(id, rect, componentManager);
    } break;
    case TypeMessage::GameDiffuculty: {
    } break;
    case TypeMessage::CreateEntityResponse: {
    } break;
    case TypeMessage::SendPlayer: {
    } break;
    case TypeMessage::ReceivePlayerInformation: {
    } break;
    }
}

void Scenes::StopGameLoop(std::shared_ptr<AudioSystem> &audioSystem)
{
    audioSystem->stopBackgroundMusic();
    audioSystem->playSoundEffect(SoundFactory(ActionType::GameOver));
    r_type::net::Message<TypeMessage> msg;
    msg.header.id = TypeMessage::DestroyEntityMessage;
    msg << _networkClient.getPlayerId();
    _networkClient.Send(msg);
    std::cout << "Closing window" << std::endl;
    _window.close();
}

void Scenes::run()
{
    while (!this->shouldQuit() && _window.isOpen()) {
        this->render();
    }
}
