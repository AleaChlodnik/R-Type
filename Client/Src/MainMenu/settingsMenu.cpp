/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** settingsMenu
*/

#include "button.hpp"
#include <vector>

int SettingsMenu()
{
    // Daltonism mode buttons, mutually exclusives
    Button *normalButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(100, 100), std::make_pair(100, 30));
    Button *tritanopiaButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(100, 200), std::make_pair(100, 30));
    Button *deuteranopiaButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(100, 300), std::make_pair(100, 30));
    Button *protanopiaButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(100, 400), std::make_pair(100, 30));
    std::vector<Button *> daltonismButtons = {
        normalButton, tritanopiaButton, deuteranopiaButton, protanopiaButton};

    // Game speed buttons, mutually exclusives
    Button *easyButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(300, 100), std::make_pair(100, 30));
    Button *mediumButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(300, 200), std::make_pair(100, 30));
    Button *hardButton =
        new Button(sf::Color(100, 100, 100), std::make_pair(300, 300), std::make_pair(100, 30));
    std::vector<Button *> gameSpeedButtons = {easyButton, mediumButton, hardButton};

    return 0;
}