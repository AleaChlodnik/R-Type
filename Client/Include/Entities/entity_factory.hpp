/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#pragma once

#include "i_entity_factory.hpp"


class EntityFactory : public IEntityFactory {
    std::shared_ptr<IEntity> createPlayer() override;
    // std::shared_ptr<IEntity> createAlly() override;
    // std::shared_ptr<IEntity> createEnemy() override;
    // std::shared_ptr<IEntity> createMonster() override;
    // std::shared_ptr<IEntity> createMissile() override;
};

