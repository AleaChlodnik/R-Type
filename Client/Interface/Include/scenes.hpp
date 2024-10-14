/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** scenes
*/

#pragma once
#include <SFML/Graphics.hpp>

class Scenes {
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

  enum class Scene
  {
    MAIN_MENU,
    GAME_LOOP,
    SETTINGS_MENU,
    IN_GAME_MENU
  };

  public:
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

  private:
    GameMode currentGameMode = GameMode::MEDIUM;
    DaltonismMode currentDaltonismMode = DaltonismMode::NORMAL;
    Scene currentScene = Scene::MAIN_MENU;
    sf::RenderWindow *_window;
};