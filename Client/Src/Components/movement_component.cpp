/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** movement_component
*/
#include "Components/movement_component.hpp"

MovementComponent::MovementComponent(
    std::pair<float, float> speed, std::pair<float, float> direction)
{
    _speed = speed;
    _direction = direction;
}

void MovementComponent::setSpeed(std::pair<float, float> speed)
{
    _speed = speed;
}

std::pair<float, float> MovementComponent::getSpeed() const { return _speed; }

void MovementComponent::setDirection(std::pair<float, float> direction)
{
    _direction = direction;
}

std::pair<float, float> MovementComponent::getDirection() const
{
    return _direction;
}
