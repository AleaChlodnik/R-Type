/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** r_type
*/

#pragma once

#include "error_handling.hpp"

class Rtype {
    public:
        Rtype(); // This will init the background, and player.
        void run(); // if main_menu variable is true, call mainMenu. While main_menu is false, call gameLoop. Get messages from the server, and store them in a queue.
        
        void mainMenu(); // Open window. (handleEvents). Display the main menu with start, help, daltonic mode, and speed selection buttons. On start, set main_menu to false, close window, and return. When active, daltonic_mode will be set to true, and draw a color filter over the screen until deactivated.
        void gameLoop(); // Open window. This is where I will call the handleEvents, updateGame, and processCommands functions.
        void handleEvents(); // This is where I will handle the events from the window.
        void updateGame(); // This is where I will update each system, entity, etc.
        void processCommands(); // This is where I will process the commands from the server. I will check the queue, call the function, then pop from queue.
};
