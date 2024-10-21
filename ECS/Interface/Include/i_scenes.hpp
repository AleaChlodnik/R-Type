#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class IScenes
 * @brief Interface for managing different scenes in a game.
 *
 * This interface declares the methods for displaying and managing various scenes in a game, such
 * as the main menu, game loop, settings menu, and in-game menu.
 */
class IScenes {
  public:
    virtual ~IScenes() = default;

    /**
     * @brief Displays the main menu and creates necessary entities.
     */
    virtual void mainMenu() = 0;

    /**
     * @brief Displays the main game loop and creates necessary entities.
     */
    virtual void gameLoop() = 0;

    /**
     * @brief Displays the settings menu and creates necessary entities.
     */
    virtual void settingsMenu() = 0;

    /**
     * @brief Displays the in-game menu and creates necessary entities.
     */
    virtual void inGameMenu() = 0;

    /**
     * @brief Displays the current scene and manages its components.
     */
    virtual void render() = 0;

    /**
     * @brief Checks if the game should quit.
     * @return True if the game should quit, false otherwise.
     */
    virtual bool shouldQuit() = 0;

    /**
     * @brief Gets the render window.
     * @return Pointer to the sf::RenderWindow.
     */
    virtual sf::RenderWindow *getRenderWindow() = 0;
};
