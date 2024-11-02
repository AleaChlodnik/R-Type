/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_scenes
*/

#pragma once

#include "Entities/entity.hpp"
#include "i_scenes.hpp"
#include <memory>

/**
 * @class AbstractScenes
 * @brief An abstract class that provides a base for managing different scenes in a game.
 *
 * This abstract class implements the ScenesInterface and provides some common functionality.
 */
class AScenes : virtual public IScenes {
  public:
    AScenes(std::string ip, int port);
    ~AScenes() = default;

    /**
     * @enum Scene
     * @brief Represents the different scenes in the R-Type client application.
     *
     * This enumeration defines the various scenes that the client can be in during its lifecycle.
     *
     * @var Scene::MAIN_MENU
     * Represents the main menu scene.
     *
     * @var Scene::GAME_LOOP
     * Represents the game loop scene where the main gameplay occurs.
     *
     * @var Scene::SETTINGS_MENU
     * Represents the settings menu scene where the user can adjust settings.
     *
     * @var Scene::IN_GAME_MENU
     * Represents the in-game menu scene that can be accessed during gameplay.
     *
     * @var Scene::EXIT
     * Represents the exit scene where the application is closing.
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
     * @enum GameMode
     * @brief Enumeration to represent different game difficulty levels.
     *
     * This enumeration defines the various difficulty levels that can be selected
     * in the game. The available modes are:
     * - EASY: Represents an easy difficulty level.
     * - MEDIUM: Represents a medium difficulty level.
     * - HARD: Represents a hard difficulty level.
     */
    enum class GameMode
    {
        EASY,
        MEDIUM,
        HARD
    };

    /**
     * @enum DaltonismMode
     * @brief Enum representing different modes of color blindness (Daltonism).
     *
     * This enum is used to specify the type of color blindness mode that can be applied.
     *
     * @var DaltonismMode::NORMAL
     * Represents normal vision without any color blindness.
     *
     * @var DaltonismMode::TRITANOPIA
     * Represents Tritanopia, a type of color blindness where blue and yellow colors are confused.
     *
     * @var DaltonismMode::DEUTERANOPIA
     * Represents Deuteranopia, a type of color blindness where green and red colors are confused.
     *
     * @var DaltonismMode::PROTANOPIA
     * Represents Protanopia, a type of color blindness where red and green colors are confused.
     */
    enum class DaltonismMode
    {
        NORMAL,
        TRITANOPIA,
        DEUTERANOPIA,
        PROTANOPIA
    };

    /**
     * @enum Actions
     * @brief Enumeration representing possible actions in the game.
     *
     * This enumeration defines the various actions that can be performed
     * by the player in the game. The actions include:
     * - UP: Move up
     * - DOWN: Move down
     * - LEFT: Move left
     * - RIGHT: Move right
     * - FIRE: Fire a weapon
     * - PAUSE: Pause the game
     * - QUIT: Quit the game
     */
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

    /**
     * @enum SpriteType
     * @brief Enumeration representing the type of sprite in the game.
     *
     * This enumeration defines the different sprite types that need to be identified in the game.
     * The types include:
     * - BACKGROUND: Represents a background sprite.
     * - PLAYER: Represents a player sprite.
     * - ALLY: Represents an ally sprite.
     * - ENEMY: Represents an enemy sprite.
     * - OTHER: Represents any other type of sprite.
     */
    enum class SpriteType
    {
        BACKGROUND,
        PLAYER,
        ALLY,
        ENEMY,
        FILTER,
        WEAPON,
        POWER_UP,
        UI,
        OTHER
    };

    /**
     * @brief A map that binds game actions to specific keyboard keys.
     *
     * This map associates each action defined in the Actions enum with a corresponding
     * key from the sf::Keyboard::Key enumeration. It is used to handle user input
     * by mapping key presses to game actions.
     *
     * The key bindings are as follows:
     * - Actions::UP -> sf::Keyboard::Key::Up
     * - Actions::DOWN -> sf::Keyboard::Key::Down
     * - Actions::LEFT -> sf::Keyboard::Key::Left
     * - Actions::RIGHT -> sf::Keyboard::Key::Right
     * - Actions::FIRE -> sf::Keyboard::Key::Space
     * - Actions::PAUSE -> sf::Keyboard::Key::Escape
     * - Actions::QUIT -> sf::Keyboard::Key::Q
     */
    std::map<Actions, sf::Keyboard::Key> keyBinds = {{Actions::UP, sf::Keyboard::Key::Up},
        {Actions::DOWN, sf::Keyboard::Key::Down}, {Actions::LEFT, sf::Keyboard::Key::Left},
        {Actions::RIGHT, sf::Keyboard::Key::Right}, {Actions::FIRE, sf::Keyboard::Key::Space},
        {Actions::PAUSE, sf::Keyboard::Key::Escape}, {Actions::QUIT, sf::Keyboard::Key::Q}};

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
    AScenes::Scene getPreviousScene();

    /**
     * @brief Get the Daltonism object
     *
     * @return DaltonismMode
     */
    DaltonismMode getDaltonism() const { return _currentDaltonismMode; };

    /**
     * @brief Set the Daltonism object
     *
     * @param mode The daltonism mode to set
     */
    void setDaltonism(DaltonismMode const mode);

    /**
     * @brief Set the Game Mode object
     *
     * @param mode
     */
    void setGameMode(GameMode const mode);

    /**
     * @brief Sets the display option for Daltonism mode.
     *
     * This function enables or disables the display option for Daltonism mode based on the provided boolean value.
     *
     * @param displayDaltonismChoice A boolean value indicating whether to display the Daltonism mode option (true) or not (false).
     */
    void setDisplayDaltonismChoice(bool const displayDaltonismChoice);

    /**
     * @brief Retrieves the current display setting for Daltonism (color blindness) mode.
     *
     * @return true if Daltonism mode is enabled, false otherwise.
     */
    bool getDisplayDaltonismChoice() const;

    /**
     * @brief Sets the display state for the game mode choice.
     *
     * This function allows you to control whether the game mode choice
     * should be displayed or not.
     *
     * @param displayGameModeChoice A boolean value indicating whether
     * the game mode choice should be displayed (true) or hidden (false).
     */
    void setDisplayGameModeChoice(bool const displayGameModeChoice);

    /**
     * @brief Retrieves the current display game mode choice.
     *
     * This function returns a boolean value indicating whether the game mode
     * choice is currently set to be displayed.
     *
     * @return true if the game mode choice is set to be displayed, false otherwise.
     */
    bool getDisplayGameModeChoice() const;

    /**
     * @brief Sets the display status for key binds choice.
     *
     * This function allows you to enable or disable the display of key binds choice.
     *
     * @param displayKeyBindsChoice A boolean value indicating whether to display the key binds choice (true) or not (false).
     */
    void setDisplayKeyBindsChoice(bool const displayKeyBindsChoice);

    /**
     * @brief Retrieves the current choice for displaying key bindings.
     *
     * @return true if key bindings should be displayed, false otherwise.
     */
    bool getDisplayKeyBindsChoice() const;

    /**
     * @brief A collection of shared pointers to Entity objects representing buttons.
     *
     * This vector holds shared pointers to Entity instances, which are used to represent
     * buttons within the scene. The use of shared pointers ensures that the Entity objects
     * are properly managed and their memory is automatically deallocated when they are no
     * longer in use.
     */
    std::vector<std::shared_ptr<Entity>> buttons;
    /**
     * @brief A shared pointer to an Entity object.
     *
     * This smart pointer manages the lifetime of an Entity instance,
     * ensuring that the Entity is properly deleted when no longer in use.
     * It allows multiple parts of the program to share ownership of the Entity.
     */
    std::shared_ptr<Entity> filter;
    /**
     * @brief Sets the IP address.
     *
     * This function sets the IP address to the specified value.
     *
     * @param ip The IP address to set as a string.
     */
    void setIp(std::string ip);
    /**
     * @brief Sets the port number for the connection.
     *
     * This function assigns the specified port number to be used for network communication.
     *
     * @param port The port number to be set.
     */
    void setPort(int port);

    /**
     * @brief Retrieves the IP address.
     *
     * This function returns the IP address as a string.
     *
     * @return std::string The IP address.
     */
    std::string getIp() const;
    /**
     * @brief Retrieves the port number.
     *
     * @return int The port number.
     */
    int getPort() const;

  protected:
    /**
     * @brief Represents the current game mode.
     *
     * This variable holds the current game mode of the game.
     * It is initialized to GameMode::MEDIUM by default.
     */
    GameMode _currentGameMode = GameMode::MEDIUM;
    /**
     * @brief Enum representing different modes of Daltonism (color blindness).
     *
     * This enum is used to specify the current Daltonism mode, which can be used
     * to adjust the display settings for users with different types of color blindness.
     *
     * Possible values:
     * - NORMAL: No color blindness.
     * - PROTANOPIA: Red color blindness.
     * - DEUTERANOPIA: Green color blindness.
     * - TRITANOPIA: Blue color blindness.
     */
    DaltonismMode _currentDaltonismMode = DaltonismMode::NORMAL;
    /**
     * @brief Represents the current scene in the application.
     *
     * This variable holds the current scene being displayed or interacted with
     * in the application. It is initialized to the MAIN_MENU scene by default.
     */
    Scene _currentScene = Scene::MAIN_MENU;
    /**
     * @brief Represents the previous scene in the application.
     *
     * This variable holds the previous scene that was active before the current one.
     * It is initialized to the MAIN_MENU scene by default.
     */
    Scene _previousScene = Scene::MAIN_MENU;
    /**
     * @brief Flag to indicate whether the Daltonism choice should be displayed.
     */
    bool _displayDaltonismChoice = false;
    /**
     * @brief Flag indicating whether the game mode choice should be displayed.
     */
    bool _displayGameModeChoice = false;
    /**
     * @brief Flag indicating whether the key bindings choice should be displayed.
     */
    bool _displayKeyBindsChoice = false;

    /**
     * @brief The IP address of the server.
     *
     * This member variable stores the IP address of the server to which
     * the client will connect. It is a string that contains the IP address
     * in the format "xxx.xxx.xxx.xxx".
     */
    std::string _ip;
    /**
     * @brief The port number of the server.
     *
     * This member variable stores the port number of the server to which
     * the client will connect. It is an integer that represents the port
     * number on which the server is listening for incoming connections.
     */
    int _port;
};
