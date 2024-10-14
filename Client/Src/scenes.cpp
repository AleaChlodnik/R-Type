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

void Scenes::setScene(Scenes::Scene scene)
{
    this->previousScene = this->currentScene;
    this->currentScene = scene;
}

void handleEvents(sf::Event event, ComponentManager &componentManager, sf::RenderWindow *_window, std::vector<Entity *> buttons, Scenes *scenes)
{
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
                if (sprite)
                if (posComp && sprite) {
                sf::Vector2u spriteSize = sprite.value()->sprite.getTexture()->getSize();
                    if (pos.x >= posComp.value()->x && pos.x <= posComp.value()->x + spriteSize.x &&
                        pos.y >= posComp.value()->y && pos.y <= posComp.value()->y + spriteSize.y) {
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

    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);

    // Create the buttons
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
    buttons = {};

    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);
    Entity player = entityFactory.createPlayer(entityManager, componentManager, textureManager);
    ShootSystem shootSystem(player.getId(), 0.5f);
    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::GAME_LOOP) {
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
                if (event.key.code == sf::Keyboard::Escape) {
                    this->setScene(Scenes::Scene::IN_GAME_MENU);
                }
            }
        }

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);
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

    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);
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
        renderSystem.render(entityManager, componentManager);
    }
}

void createDaltonismChoiceButtons(std::vector<Entity *> buttons, ComponentManager &componentManager, EntityManager &entityManager, TextureManager &textureManager, EntityFactory &entityFactory)
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
    Entity tritanopiaButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Tritanopia", &onTritanopiaButtonClicked);
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
    Entity protanopiaButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Protanopia", &onProtanopiaButtonClicked);
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

void createGameModeChoiceButtons(std::vector<Entity *> buttons, ComponentManager &componentManager, EntityManager &entityManager, TextureManager &textureManager, EntityFactory &entityFactory)
{
    std::function<Scenes *(Scenes *)> easyButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::EASY);
        return currentScene;
    };
    Entity easyButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Easy", &easyButtonClicked);
    auto pos = componentManager.getComponent<PositionComponent>(easyButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 250;
    }

    std::function<Scenes *(Scenes *)> mediumButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::MEDIUM);
        return currentScene;
    };
    Entity mediumButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Medium", &mediumButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(mediumButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 400;
    }

    std::function<Scenes *(Scenes *)> hardButtonClicked = [](Scenes *currentScene) {
        currentScene->setGameMode(Scenes::GameMode::HARD);
        return currentScene;
    };
    Entity hardButton = entityFactory.createButton(entityManager, componentManager,
        textureManager, "Hard", &hardButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(hardButton.getId());
    if (pos) {
        pos.value()->x = 1260;
        pos.value()->y = 550;
    }

    buttons.push_back(&easyButton);
    buttons.push_back(&mediumButton);
    buttons.push_back(&hardButton);
}

void Scenes::settingsMenu()
{
    ComponentManager componentManager;
    EntityManager entityManager;
    TextureManager textureManager;
    EntityFactory entityFactory;
    UpdateSystem updateSystem(*_window);
    RenderSystem renderSystem(*_window);
    buttons = {};

    // Create all the necessary entities
    Entity background =
        entityFactory.createBackground(entityManager, componentManager, textureManager);

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

    std::function<Scenes *(Scenes *)> onBackButtonClicked = [](Scenes *currentScene) {
        currentScene->setScene(Scenes::Scene::MAIN_MENU);
        return currentScene;
    };
    Entity backButton = entityFactory.createButton(
        entityManager, componentManager, textureManager, "Back", &onBackButtonClicked);
    pos = componentManager.getComponent<PositionComponent>(backButton.getId());
    if (pos) {
        pos.value()->x = 760;
        pos.value()->y = 500;
    }

    buttons.push_back(&daltonismModeButton);
    buttons.push_back(&gameModeButton);
    buttons.push_back(&backButton);

    if (displayDaltonismChoice)
        createDaltonismChoiceButtons(buttons, componentManager, entityManager, textureManager, entityFactory);
    if (displayGameModeChoice)
        createGameModeChoiceButtons(buttons, componentManager, entityManager, textureManager, entityFactory);

    sf::Clock clock;
    sf::Event event;

    while (_window->isOpen() && this->currentScene == Scenes::Scene::SETTINGS_MENU) {

        handleEvents(event, componentManager, _window, buttons, this);

        float deltaTime = clock.restart().asSeconds();

        updateSystem.update(entityManager, componentManager, deltaTime);
        renderSystem.render(entityManager, componentManager);
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