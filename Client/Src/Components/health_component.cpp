/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/
#include "health_component.hpp"

Components::HealthComponent::HealthComponent(int maxHealth)
{
    _maxHealth = maxHealth;
    _health = maxHealth;
}

void Components::HealthComponent::setHealth(int health)
{
    _health = health;
}

int Components::HealthComponent::getHealth() const
{
    return _health;
}

int Components::HealthComponent::operator+(int health)
{
    _health += health;
    return _health;
}
