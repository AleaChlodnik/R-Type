/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** player_entity
*/

#pragma once

#include "a_entity.hpp"

class PlayerEntity : public AEntity {
    public:
        PlayerEntity(int maxHealth = 100, std::pair<float, float> startingPos = std::make_pair(0, 0))
            : _maxHealth(maxHealth), _startingPos(startingPos) {}

        int getMaxHealth() const { return _maxHealth; }
    
    private:
        std::vector<std::shared_ptr<AComponent>> components;

        const int _maxHealth;
        //const std::pair<float, float> _size;
        const std::pair<float, float> _startingPos;
};

