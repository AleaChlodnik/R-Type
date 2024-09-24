/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_system
*/

#pragma once

#include <memory>

class Entity;

class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update() = 0;
        virtual void addEntity(std::shared_ptr<Entity> entity) = 0;
};
