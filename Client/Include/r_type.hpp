/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#pragma once

#include "error_handling.hpp"

class Rtype {

    enum class GameMode {
        EASY,
        MEDIUM,
        HARD
    };

    enum class DaltonismMode {
        NORMAL,
        TRITANOPIA,
        DEUTERANOPIA,
        PROTANOPIA
    };

    public:
        Rtype(); // This will init the background, and player. Set daltonic_mode to false, and main_menu to true. Ex: renderSystem.addEntity(player), inputSystem.addEntity(player), collisionSystem.addEntity(player), etc. Default easy mode and normal daltonism mode.
        void run(); // If main_menu variable is true, call mainMenu. While main_menu is false, call gameLoop. Get messages from the server, and store them in a queue (maybe?).
        
        void mainMenu(); // Open window. (handleEvents). Display the main menu with start, help, daltonic mode, and speed selection buttons. On start, set main_menu to false, close window, and return. When active, daltonic_mode will be set to true, and draw a color filter over the screen until deactivated.
        void gameLoop(); // Open window. This is where I will call the handleEvents, updateGame, processCommands, and render functions.
        void handleEvents(); // This is where I will handle the events for the window & player (key input, etc.).
        void updateGame(); // This is where I will update the time, position of sprites, etc. Ex: inputSystem.update(deltaTime.asSeconds()), renderSystem.update(deltaTime.asSeconds()), etc.
        void processCommands(); // This is where I will process the commands from the server. I will check the queue, call the function, then pop from queue.
        void renderGame(); // Ex: window.clear(), window.draw(background), renderSystem.render(window), window.display, etc.

        // Setters
        void setGameMode(GameMode mode) { currentGameMode = mode; }
        void setDaltonismMode(DaltonismMode mode) { currentDaltonismMode = mode; }
        void setMainMenuStatus(bool status) { main_menu = status; }
        // Getters
        GameMode getGameMode() const { return currentGameMode; }
        DaltonismMode getDaltonismMode() const { return currentDaltonismMode; }
        int getMainMenuStatus() const { return main_menu; }

    private:
        GameMode currentGameMode;
        DaltonismMode currentDaltonismMode;
        bool main_menu;
};
