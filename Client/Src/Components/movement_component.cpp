/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** movement_component
*/
#include "../../Include/Components/movement_component.hpp"

Components::MovementComponent::MovementComponent(std::pair<float, float> speed, std::pair<float, float> direction)
{
    _speed = speed;
    _direction = direction;
}

void Components::MovementComponent::setSpeed(std::pair<float, float> speed)
{
    _speed = speed;
}

std::pair<float, float> Components::MovementComponent::getSpeed() const
{
    return _speed;
}

void Components::MovementComponent::setDirection(std::pair<float, float> direction)
{
    _direction = direction;
}

std::pair<float, float> Components::MovementComponent::getDirection() const
{
    return _direction;
}

