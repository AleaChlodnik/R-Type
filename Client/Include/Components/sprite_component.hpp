/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/
#pragma once

#include "a_component.hpp"
#include <SFML/Graphics.hpp>

class SpriteComponent : public AComponent {
  public:
    SpriteComponent(std::string path, std::pair<float, float> size,
        std::pair<float, float> position);
    SpriteComponent(std::string path);

    const sf::Texture &getTexture() const;
    void setTexture(std::string path);
    void setSpritePosition(std::pair<float, float> position);
    std::pair<int, int> getSpritePosition() const;
    void setSpriteSize(std::pair<float, float> size);
    std::pair<float, float> getSpriteSize() const;

  private:
    sf::Texture _texture;
    std::string path;
    sf::Sprite _sprite;
};
