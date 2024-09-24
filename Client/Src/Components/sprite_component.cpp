/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/
#include "Components/sprite_component.hpp"

SpriteComponent::SpriteComponent(std::string path, std::pair<float, float> size, std::pair<float, float> position)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, size.first, size.second));
    _sprite.setPosition(position.first, position.second);
}

SpriteComponent::SpriteComponent(std::string path)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
}

const sf::Texture &SpriteComponent::getTexture() const
{
    return _texture;
}

void SpriteComponent::setSpritePosition(std::pair<float, float> position)
{
    _sprite.setPosition(position.first, position.second);
}

std::pair<int, int> SpriteComponent::getSpritePosition() const
{
    return std::make_pair(_sprite.getPosition().x, _sprite.getPosition().y);
}

void SpriteComponent::setSpriteSize(std::pair<float, float> size)
{
    _sprite.setTextureRect(sf::IntRect(0, 0, size.first, size.second));
}

std::pair<float, float> SpriteComponent::getSpriteSize() const
{
    return std::make_pair(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
}

void SpriteComponent::setTexture(std::string path)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
}
