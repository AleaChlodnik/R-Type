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
        SpriteComponent(const std::string &path, std::pair<float, float> size, std::pair<float, float> position);

        void setTexture(const std::string &path);
        void setSpritePosition(std::pair<float, float> position);
        void setSpriteSize(std::pair<float, float> size);
    
        const sf::Texture &getTexture() { return _texture; }
        std::pair<float, float> getSpritePosition();
        std::pair<float, float> getSpriteSize();

        sf::Sprite &getSprite() { return _sprite; }

    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        const std::string _type = "sprite";
};
