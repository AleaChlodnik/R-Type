/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** text_component
*/

#pragma once

#include <SFML/Graphics.hpp>

struct TextComponent {
    sf::Text text;

    TextComponent(sf::Font &font, const std::string &string, float posX, float posY, int size = 30)
    {
        text.setCharacterSize(size);
        text.setFont(font);
        text.setString(string);
        text.setPosition(posX, posY);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
    }
};
