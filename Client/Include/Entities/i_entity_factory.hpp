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
        virtual std::shared_ptr<IEntity> createPlayer() = 0;
        // virtual std::shared_ptr<IEntity> createAlly() = 0;
        // virtual std::shared_ptr<IEntity> createEnemy() = 0;
        // virtual std::shared_ptr<IEntity> createMonster() = 0;
        // virtual std::shared_ptr<IEntity> createMissile() = 0;
};

