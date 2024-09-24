/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_system
*/

#pragma once

#include <memory>

class AEntity;

namespace Systems {
class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update() = 0;
        virtual void addEntity(std::shared_ptr<AEntity> entity) = 0;
};
};
