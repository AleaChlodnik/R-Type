/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** text_component
*/

#pragma once

#include <SFML/Graphics.hpp>

/**
 * @struct TextComponent
 * @brief A component that encapsulates an SFML text object.
 *
 * This component is used to manage and render text in an SFML application.
 *
 * @var sf::Text TextComponent::text
 * The SFML text object that this component encapsulates.
 *
 * @fn TextComponent::TextComponent(sf::Font &font, const std::string &string, float posX, float
 * posY, int size = 30)
 * @brief Constructs a TextComponent with the specified parameters.
 *
 * @param font The font to be used for the text.
 * @param string The string to be displayed.
 * @param posX The x-coordinate of the text's position.
 * @param posY The y-coordinate of the text's position.
 * @param size The character size of the text. Default is 30.
 */
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
