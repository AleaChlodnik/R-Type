/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** button
*/
#include "../../Include/button.hpp"

Button::Button(std::string path, std::pair<int, int> position,
    std::pair<float, float> size)
{
    this->font.loadFromFile("Client/Src/Assets/godofwar.ttf");
    this->text.setFont(font);
    this->text.setString("Button");
    this->text.setPosition(position.first, position.second);
    this->text.setCharacterSize(this->fontSize);
    this->bgImage.loadFromFile(path);
    this->sprite.setTexture(this->bgImage);
    this->sprite.setPosition(position.first, position.second);
    this->sprite.setScale(size.first, size.second);
    this->setSize(size);
}

void Button::setSize(std::pair<float, float>)
{
    sf::Vector2u currentSize = this->bgImage.getSize();
    this->sprite.setScale(currentSize.x / this->bgImage.getSize().x,
        currentSize.y / this->bgImage.getSize().y);
}

std::pair<float, float> Button::getSize()
{
    return std::make_pair(
        this->sprite.getScale().x, this->sprite.getScale().y);
}

void Button::setText(std::string text) { this->text.setString(text); }

std::string Button::getText() { return this->text.getString(); }

void Button::setFont(std::string path)
{
    this->font.loadFromFile(path);
    this->text.setFont(this->font);
}

void Button::setPosition(std::pair<int, int> position)
{
    this->sprite.setPosition(position.first, position.second);
    this->text.setPosition(position.first, position.second);
}

std::pair<int, int> Button::getPosition()
{
    return std::make_pair(
        this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
    window.draw(this->text);
}

void Button::setTexture(std::string texturePath)
{
    this->bgImage.loadFromFile(texturePath);
}

void Button::setFontSize(std::size_t fontSize)
{
    this->fontSize = fontSize;
    this->text.setCharacterSize(this->fontSize);
}

void Button::setOnClick(std::function<void(Rtype)> callback)
{
    this->onClick = callback;
}

void Button::setOnHover(std::function<void(Rtype)> callback)
{
    this->onHover = callback;
}
