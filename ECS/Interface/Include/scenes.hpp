/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#pragma once

#include "Entities/entity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @class Scenes
 * @brief Represents a class that manages different scenes in a game.
 *
 * The Scenes class provides functionality to display and manage various scenes in a game, such as
 * the main menu, game loop, settings menu, and in-game menu. It also allows setting the game mode
 * and daltonism mode.
 */
class Scenes {

  public:
    /*/**
     * @brief
     *
     */
    enum class Scene
    {
        MAIN_MENU,
        GAME_LOOP,
        SETTINGS_MENU,
        IN_GAME_MENU,
        EXIT
    };

    /**
     * @brief Enumeration representing different game modes.
     *
     */
    enum class GameMode
    {
        EASY,
        MEDIUM,
        HARD
    };

    /**
     * @brief Enum class representing different modes of Daltonism.
     *
     */
    enum class DaltonismMode
    {
        NORMAL,
        TRITANOPIA,
        DEUTERANOPIA,
        PROTANOPIA
    };

    enum class Actions
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FIRE,
        PAUSE,
        QUIT
    };

    enum class SpriteType
    {
        BACKGROUND,
        PLAYER,
        ALLY,
        ENEMY,
        OTHER
    };

    std::map<Actions, sf::Keyboard::Key> keyBinds = {{Actions::UP, sf::Keyboard::Key::Up},
        {Actions::DOWN, sf::Keyboard::Key::Down}, {Actions::LEFT, sf::Keyboard::Key::Left},
        {Actions::RIGHT, sf::Keyboard::Key::Right}, {Actions::FIRE, sf::Keyboard::Key::Space},
        {Actions::PAUSE, sf::Keyboard::Key::Escape}, {Actions::QUIT, sf::Keyboard::Key::Q}};

  public:
    /**
     * @brief Construct a new Scenes object
     *
     * @param window
     */
    Scenes(sf::RenderWindow *window);

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
     * @brief display what must be displayed (main menu, game loop, settings menu, in game menu),
     *        creates all the components needed and manages them
     *
     */
    void render();

    /**
     * @brief Set the Daltonism object
     *
     * @param mode The daltonism mode to set
     */
    void setDaltonism(DaltonismMode mode) { currentDaltonismMode = mode; }
    /**
     * @brief Set the Game Mode object
     *
     * @param mode
     */
    void setGameMode(GameMode mode) { currentGameMode = mode; }
    /**
     * @brief Set the Scene object
     *
     * @param scene
     */
    void setScene(Scene scene);
    /**
     * @brief Get the Previous Scene object
     *
     * @return Scene
     */
    Scene getPreviousScene() { return previousScene; }
    /**
     * @brief check if game should stop running
     *
     * @return true
     * @return false
     */
    bool shouldQuit() { return currentScene == Scene::EXIT; }
    /**
     * @brief Get the RenderWindow object
     *
     * @return sf::RenderWindow*
     */
    sf::RenderWindow *getRenderWindow() { return _window; }

  private:
    /**
     * @brief the current game mode
     *
     */
    GameMode currentGameMode = GameMode::MEDIUM;
    /**
     * @brief the current daltonism mode
     *
     */
    DaltonismMode currentDaltonismMode = DaltonismMode::NORMAL;
    /**
     * @brief the current scene
     *
     */
    Scene currentScene = Scene::MAIN_MENU;
    Scene previousScene = Scene::MAIN_MENU;
    bool displayDaltonismChoice = false;
    bool displayGameModeChoice = false;
    bool displayKeyBinds = false;
    /**
     * @brief the window
     *
     */
    sf::RenderWindow *_window;
    std::vector<std::shared_ptr<Entity>> buttons;
    sf::Keyboard::Key binding;
};