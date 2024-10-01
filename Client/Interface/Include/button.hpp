/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** button
*/
#include "r_type.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

#pragma once

class Button {
  public:
    Button() = default;
    Button(std::string path);
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
    void setOnClick(std::function<void(Rtype)> callback);
    void setOnHover(std::function<void(Rtype)> callback);

    void render(sf::RenderWindow &window);

    std::function<void(Rtype)> onClick;
    std::function<void(Rtype)> onHover;

  private:
    sf::Texture bgImage;
    sf::Sprite sprite;
    sf::Text text;
    sf::Font font;
    std::size_t fontSize = 12;
};