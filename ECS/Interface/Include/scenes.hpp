/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#pragma once

#include "Entities/entity.hpp"
#include <SFML/Graphics.hpp>

class Scenes {

    enum class Scene
    {
        MAIN_MENU,
        GAME_LOOP,
        SETTINGS_MENU,
        IN_GAME_MENU,
        EXIT
    };

  public:
    enum class GameMode
    {
        EASY,
        MEDIUM,
        HARD
    };

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

    std::map<Actions, sf::Keyboard::Key> keyBinds = {
      {Actions::UP, sf::Keyboard::Key::W},
      {Actions::DOWN, sf::Keyboard::Key::S},
      {Actions::LEFT, sf::Keyboard::Key::A},
      {Actions::RIGHT, sf::Keyboard::Key::D},
      {Actions::FIRE, sf::Keyboard::Key::Space},
      {Actions::PAUSE, sf::Keyboard::Key::Escape},
      {Actions::QUIT, sf::Keyboard::Key::Q}
    };

    Scenes(sf::RenderWindow *window);
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
     * @param mode
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

  private:
    GameMode currentGameMode = GameMode::MEDIUM;
    DaltonismMode currentDaltonismMode = DaltonismMode::NORMAL;
    Scene currentScene = Scene::MAIN_MENU;
    Scene previousScene = Scene::MAIN_MENU;
    bool displayDaltonismChoice = false;
    bool displayGameModeChoice = false;
    sf::RenderWindow *_window;
    std::vector<Entity *> buttons;
};