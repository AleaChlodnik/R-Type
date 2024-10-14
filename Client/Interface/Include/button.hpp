/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** button
*/

#pragma once

#include "scenes.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

class Button {
  public:
    Button() = default;
    Button(std::string path);
    Button(sf::Color color, std::pair<int, int> position, std::pair<float, float> size);
    Button(std::string path, std::pair<int, int> position);
    Button(std::string path, std::pair<int, int> position, std::pair<float, float> size);
    ~Button() = default;

    void setFont(std::string fontPath);
    void setPosition(std::pair<int, int>);
    std::pair<int, int> getPosition();
    void setSize(std::pair<float, float>);
    std::pair<float, float> getSize();
    void setText(std::string);
    std::string getText();
    void setTexture(std::string texturePath);
    void setFontSize(std::size_t fontSize);
    void setOnClick(std::function<void(Scenes *)> callback);
    void setOnHover(std::function<void(Scenes *)> callback);
    bool isHovered(std::pair<int, int> mousePos);

    void render(sf::RenderWindow &window);

    std::function<void(Scenes *)> onClick;
    std::function<void(Scenes *)> onHover;

  private:
    sf::Texture *bgImage = new sf::Texture();
    sf::RectangleShape rect = sf::RectangleShape();
    sf::Text text = sf::Text();
    sf::Font font = sf::Font();
    std::size_t fontSize = 12;
};