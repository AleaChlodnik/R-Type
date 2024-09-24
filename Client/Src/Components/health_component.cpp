/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/
#include "Components/health_component.hpp"

HealthComponent::HealthComponent(int maxHealth)
{
    _maxHealth = maxHealth;
    _health = maxHealth;
}

void HealthComponent::setHealth(int health)
{
    _health = health;
}

int HealthComponent::getHealth() const
{
    return _health;
}

int HealthComponent::operator+(int health)
{
    _health += health;
    return _health;
}
