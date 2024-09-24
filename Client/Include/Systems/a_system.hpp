/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_system
*/

#pragma once

#include <memory>
#include <vector>

#include "i_system.hpp"

class ASystem : public ISystem {
    public:
        virtual ~ASystem() override = default;
        void addEntity(std::shared_ptr<Entity> entity) override { _entities.push_back(entity); }
    
    protected:
        std::vector<std::shared_ptr<Entity>> _entities;
};
