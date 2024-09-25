/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sprite_component
*/
#include "Components/sprite_component.hpp"

SpriteComponent::SpriteComponent(const std::string &path, std::pair<float, float> size, std::pair<float, float> position)
{
    setTexture(path);
    setSpriteSize(size);
    setSpritePosition(position);
}

void SpriteComponent::setTexture(const std::string &path)
{
    if (!_texture.loadFromFile(path))
        throw failedToLoadTexture();
    
    _sprite.setTexture(_texture);
}

void SpriteComponent::setSpritePosition(std::pair<float, float> position)
{
    _sprite.setPosition(position.first, position.second);
}

std::pair<float, float> SpriteComponent::getSpritePosition()
{
    sf::Vector2f pos = _sprite.getPosition();
    return {pos.x, pos.y};
}

std::pair<float, float> SpriteComponent::getSpriteSize()
{
    sf::Vector2f scale = _sprite.getScale();
    return {scale.x, scale.y};
}

void SpriteComponent::setSpriteSize(std::pair<float, float> size)
{
    if (_texture.getSize().x > 0 && _texture.getSize().y > 0) {
        _sprite.setScale(size.first / _texture.getSize().x,
            size.second / _texture.getSize().y);
    }
}
