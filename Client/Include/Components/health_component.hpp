/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/
#pragma once

#include "a_component.hpp"

class HealthComponent : public AComponent {
  public:
    HealthComponent(int maxHealth);

    void setHealth(int health);
    int getHealth() const;

    int operator+(int health);

  private:
    int _health;
    int _maxHealth;
};
