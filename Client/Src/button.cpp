/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** button
*/
#include <button.hpp>

Button::Button(std::string path, std::pair<int, int> position, std::pair<float, float> size)
{
    this->font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF");
    this->text.setFont(font);
    this->text.setString("Button");
    this->text.setPosition(position.first, position.second);
    this->text.setCharacterSize(this->fontSize);
    this->bgImage->loadFromFile(path);
    this->rect.setTexture(this->bgImage);
    this->rect.setPosition(position.first, position.second);
    this->rect.setSize(sf::Vector2f(size.first, size.second));
    this->setSize(size);
}

Button::Button(std::string path) { this->bgImage->loadFromFile(path); }

Button::Button(sf::Color color, std::pair<int, int> position, std::pair<float, float> size)
{
    this->font.loadFromFile("Client/Assets/Fonts/GODOFWAR.TTF");
    this->text.setFont(font);
    this->text.setString("Button");
    this->text.setPosition(position.first, position.second);
    this->text.setCharacterSize(this->fontSize);
    this->rect.setPosition(position.first, position.second);
    this->rect.setSize(sf::Vector2f(size.first, size.second));
    this->rect.setFillColor(color);
    double luminance = (0.299 * color.r + 0.587 * color.g + 0.114 * color.b) / 255.0;
    sf::Color *dacolor = new sf::Color;
    (luminance > 0.5) ? dacolor->Black : dacolor->White;
    this->text.setColor(*dacolor);
    this->setSize(size);
}

void Button::setSize(std::pair<float, float> size)
{
    this->rect.setSize(sf::Vector2f(size.first, size.second));
}

std::pair<float, float> Button::getSize()
{
    return std::make_pair(this->rect.getSize().x, this->rect.getSize().y);
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
    this->rect.setPosition(position.first, position.second);
    this->text.setPosition(position.first, position.second);
}

std::pair<int, int> Button::getPosition()
{
    return std::make_pair(this->rect.getPosition().x, this->rect.getPosition().y);
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(this->rect);
    window.draw(this->text);
}

void Button::setTexture(std::string texturePath) { this->bgImage->loadFromFile(texturePath); }

void Button::setFontSize(std::size_t fontSize)
{
    this->fontSize = fontSize;
    this->text.setCharacterSize(this->fontSize);
}

void Button::setOnClick(std::function<void(Scenes *)> callback) { this->onClick = callback; }

void Button::setOnHover(std::function<void(Scenes *)> callback) { this->onHover = callback; }

bool Button::isHovered(std::pair<int, int> mousePos)
{
    return this->rect.getGlobalBounds().contains(mousePos.first, mousePos.second);
}