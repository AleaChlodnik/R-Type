/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity_factory
*/

#pragma once

#include <memory>

#include "i_entity.hpp"


// Abstract Entity Factory
class IEntityFactory {
    public:
        virtual ~IEntityFactory() = default;
        virtual std::shared_ptr<AEntity> createPlayer() = 0;
};

