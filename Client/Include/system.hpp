/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system
*/

#pragma once

#include <memory>
#include <vector>

#include "error_handling.hpp"
#include "entity.hpp"

class System {
    public:
        virtual ~System() = default;
        virtual void update() = 0;
        void addEntity(std::shared_ptr<Entity> entity);
    
    protected:
	    std::vector<std::shared_ptr<Entity>> entities;
};
