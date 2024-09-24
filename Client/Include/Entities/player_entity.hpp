/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** player_entity
*/

#pragma once

#include "a_entity.hpp"

namespace Entities {
    class PlayerEntity : public AEntity {
        public:
            PlayerEntity() {};
        
        private:
            std::vector<std::shared_ptr<AComponent>> components;
    
            int _maxHealth = 100;
            std::string _name = "player";
    };
};
