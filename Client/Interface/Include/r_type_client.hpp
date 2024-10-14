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

class Rtype {

  public:
    /**
     * @brief Construct a new Rtype object
     * This will init the player. Default easy mode and normal
     * daltonism mode. Ex: renderSystem.addEntity(player),
     * inputSystem.addEntity(player),
     * collisionSystem.addEntity(player), etc.
     */
    Rtype();

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
    Scenes *_scenes;
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
