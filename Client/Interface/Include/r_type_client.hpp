/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#pragma once

#include "error_handling.hpp"
#include "scenes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/**
 * @class Rtype
 * @brief The Rtype class handles the main game logic, including initialization, main menu, game
 * loop, event handling, server message processing, game updating, and rendering.
 *
 * The Rtype class is responsible for initializing the player, managing the main menu, running the
 * game loop, handling events, processing server messages, updating the game state, and rendering
 * the game.
 *
 * @section Usage
 * To use the Rtype class, create an instance of it and call the run() method to start the game.
 *
 * @code
 * Rtype game;
 * game.run();
 * @endcode
 *
 * @section Methods
 * - Rtype(): Constructs a new Rtype object and initializes the player.
 * - void run(): Starts the main loop of the game, switching between the main menu and the game
 * loop based on the _mainMenu variable.
 * - void mainMenu(): Displays the main menu with options to start the game, view help, toggle
 * daltonic mode, and select speed. Handles user input for these options.
 * - void gameLoop(): Runs the main game loop, calling handleEvents, updateGame, processCommands,
 * and render functions.
 * - void handleEvents(): Handles window and player events, such as key input, and sends updated
 * player information to the server.
 * - void processServerMessages(): Processes messages received from the server.
 * - void updateGame(): Updates the game state, including time, position of sprites, and other game
 * elements.
 * - void renderGame(): Renders the game, including clearing the window, drawing the background,
 * rendering game elements, and displaying the window.
 *
 * @section Private Members
 * - Scenes *_scenes: Pointer to the scenes object.
 * - sf::RenderWindow _window: The window object used for rendering the game.
 */
class Rtype {

  public:
    /**
     * @brief Construct a new Rtype object
     * This will init the player. Default easy mode and normal
     * daltonism mode. Ex: renderSystem.addEntity(player),
     * inputSystem.addEntity(player),
     * collisionSystem.addEntity(player), etc.
     */
    Rtype(std::string ip, int port);

    /**
     * @brief If _mainMenu variable is true, call mainMenu. While
     * _mainMenu is false, call gameLoop.
     *
     */
    void run();

    /**
     * @brief Open window. (handleEvents). Display the main menu with
     * start, help, daltonic mode, and speed selection buttons. On
     * start, set _mainMenu to false, close window, and return.
     * When active, daltonic_mode will be set to true, and draw a
     * color filter over the screen until deactivated. Can set
     * keybindings as well, either default or customized
     *
     */
    void mainMenu();
    /**
     * @brief Open window. This is where I will call the handleEvents,
     * updateGame, processCommands, and render functions.
     *
     */
    void gameLoop();

    /**
     * @brief This is where I will handle the events for the window &
     * player (key input, etc.). When key is pressed, move
     * player, and send new player info to server.
     */
    void handleEvents();

    /**
     * @brief This is where I will process the info from the server.
     */
    void processServerMessages();

    /**
     * @brief This is where I will update the time, position of sprites, etc. Ex:
     * inputSystem.update(deltaTime.asSeconds()), renderSystem.update(deltaTime.asSeconds()), etc.
     *
     */
    void updateGame();

    /**
     * @brief This is where I will render the game. Ex: window.clear(), window.draw(background),
     * renderSystem.render(window), window.display, etc.
     *
     */
    void renderGame();

    // Setters
    /**
     * @brief Set the Game Mode object
     *
     * @param mode
     */

  private:
    /**
     * @brief Pointer to the Scenes object.
     *
     * This member variable holds a pointer to an instance of the Scenes class,
     * which is used to manage and control different scenes within the client.
     */
    Scenes *_scenes;
    /**
     * @brief The main window for rendering graphics.
     *
     * This member represents the window where all the graphical
     * content of the application will be displayed. It is an instance
     * of the sf::RenderWindow class from the SFML library.
     */
    sf::RenderWindow _window;
};

/*
** create entity from factory
** call addEntityToSystems(entity)
** in function: addEntityToSystems(entity):
** use switch case to see which entity it is, and add to the correct system
*/

/*
** creat system manager to make updating easier?
*/
