/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** display
*/
#include "button.hpp"

int MainMenu(sf::RenderWindow &window)
{
    Button *playButton = new Button(
        "Client/Src/Assets/button.png", std::make_pair(100, 100), std::make_pair(100, 30));
    playButton->setFont("Client/Src/Assets/godofwar.ttf");
    playButton->setText("Play");
    playButton->render(window);

    Button *settingsButton = new Button(
        "Client/Src/Assets/button.png", std::make_pair(100, 200), std::make_pair(100, 30));
    settingsButton->setFont("Client/Src/Assets/godofwar.ttf");
    settingsButton->setText("Settings");
    settingsButton->render(window);
    return 0;
}