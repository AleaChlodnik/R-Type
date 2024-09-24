/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/
#pragma once
#include "a_component.hpp"

namespace Components {

    class HealthComponent : public AComponent {
        public:
            HealthComponent() = default;
            HealthComponent(int health);
            
            void setHealth(int health);
            int getHealth() const;
            void setMaxHealth(int maxHealth);
            int getMaxHealth() const;

            int operator+(int health);
        private:
            int _health;
            int _maxHealth;
    };

}
