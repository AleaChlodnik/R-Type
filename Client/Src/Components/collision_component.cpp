/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_component
*/
#include "Components/collision_component.hpp"

CollisionComponent::CollisionComponent(std::pair<float, float> size, std::pair<float, float> position)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

sf::RectangleShape CollisionComponent::getHitbox() const
{
    return this->_hitbox;
}

void CollisionComponent::setHitbox(std::pair<float, float> size, std::pair<float, float> position)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

void CollisionComponent::setHitboxPosition(std::pair<float, float> position)
{
    _hitbox.setPosition(sf::Vector2f(position.first, position.second));
}

std::pair<float, float> CollisionComponent::getHitboxPosition() const
{
    sf::Vector2f position = _hitbox.getPosition();
    return std::pair<float, float>(position.x, position.y);
}

void CollisionComponent::setHitboxSize(std::pair<float, float> size)
{
    _hitbox.setSize(sf::Vector2f(size.first, size.second));
}

std::pair<float, float> CollisionComponent::getHitboxSize() const
{
    sf::Vector2f size = _hitbox.getSize();
    return std::pair<float, float>(size.x, size.y);
}
