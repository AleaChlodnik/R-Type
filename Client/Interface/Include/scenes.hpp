/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#pragma once

#include <Entities/entity.hpp>
#include <Net/client.hpp>
#include <SFML/Graphics.hpp>
#include <Systems/systems.hpp>
#include <a_scenes.hpp>
#include <memory>
#include <vector>

std::string keyToString(sf::Keyboard::Key key);
/**
 * @class Scenes
 * @brief Represents a class that manages different scenes in a game.
 *
 * The Scenes class provides functionality to display and manage various scenes in a game, such as
 * the main menu, game loop, settings menu, and in-game menu. It also allows setting the game mode
 * and daltonism mode.
 */
class Scenes : virtual public AScenes {

  public:
    /**
     * @brief Construct a new Scenes object
     *
     * @param window
     */
    Scenes(std::string ip, int port);

    /**
     * @brief Destroy the Scenes object
     *
     */
    ~Scenes() = default;

    /**
     * @brief displays the main menu, creates all the necessary entities
     *
     */
    void mainMenu();

    /**
     * @brief displays the main game loop, creates all the necessary entities
     *
     */
    void gameLoop();

    void HandleMessage(r_type::net::Message<TypeMessage> &msg, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, std::shared_ptr<AudioSystem> &audioSystem);

    void StopGameLoop(std::shared_ptr<AudioSystem> &audioSystem);

    /**
     * @brief displays the settings menu, creates all the necessary entities
     *
     */
    void settingsMenu();

    /**
     * @brief displays the in game menu, creates all the necessary entities
     *
     */
    void inGameMenu();

    /**
     * @brief displays the difficulty choices, creates all the necessary entities
     *
     */
    void difficultyChoices();

    /**
     * @brief display what must be displayed (main menu, game loop, settings menu, in game menu),
     *        creates all the components needed and manages them
     *
     */
    void render();

    /**
     * @brief check if game should stop running
     *
     * @return true
     * @return false
     */
    bool shouldQuit() { return _currentScene == Scene::EXIT; }

    /**
     * @brief Get the RenderWindow object
     *
     * @return sf::RenderWindow*
     */
    sf::RenderWindow *getRenderWindow() { return &_window; }

    void run();

    sf::RenderWindow _window;

    r_type::net::Client _networkClient;
};