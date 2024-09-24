/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/
#include "../../Include/Components/health_component.hpp"

Components::HealthComponent::HealthComponent(int health)
{
    _health = health;
}

void Components::HealthComponent::setHealth(int health)
{
    _health = health;
}

int Components::HealthComponent::getHealth() const
{
    return _health;
}

void Components::HealthComponent::setMaxHealth(int maxHealth)
{
    _maxHealth = maxHealth;
}

int Components::HealthComponent::getMaxHealth() const
{
    return _maxHealth;
}

int Components::HealthComponent::operator+(int health)
{
    _health += health;
    return _health;
}
