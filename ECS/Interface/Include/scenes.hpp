/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#pragma once
#include <SFML/Graphics.hpp>

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

    /**
     * @brief Enumeration representing different scenes in the game.
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
    void setDaltonism(DaltonismMode mode);

    /**
     * @brief Set the Game Mode object
     *
     * @param mode
     */
    void setGameMode(GameMode mode);

    /**
     * @brief Set the Scene object
     *
     * @param scene
     */
    void setScene(Scene scene);

    /**
     * @brief Checks if the current scene should quit.
     *
     * @return true
     * @return false
     */
    bool shouldQuit() { return currentScene == Scene::EXIT; }

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
    /**
     * @brief the window
     *
     */
    sf::RenderWindow *_window;
};