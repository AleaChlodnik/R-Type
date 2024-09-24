/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_component
*/
#include "../../Include/Components/collision_component.hpp"

Components::CollisionComponent::CollisionComponent(std::pair<float, float> size, std::pair<float, float> position)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

sf::RectangleShape Components::CollisionComponent::getHitbox() const
{
    return this->_hitbox;
}

void Components::CollisionComponent::setHitbox(std::pair<float, float> size, std::pair<float, float> position)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

void Components::CollisionComponent::setHitboxPosition(std::pair<float, float> position)
{
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

std::pair<float, float> Components::CollisionComponent::getHitboxPosition() const
{
    sf::Vector2f position = _hitbox.getPosition();
    return std::pair<float, float>(position.x, position.y);
}

void Components::CollisionComponent::setHitboxSize(std::pair<float, float> size)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
}

std::pair<float, float> Components::CollisionComponent::getHitboxSize() const
{
    sf::Vector2f size = _hitbox.getSize();
    return std::pair<float, float>(size.x, size.y);
}
