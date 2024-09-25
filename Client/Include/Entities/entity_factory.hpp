/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#pragma once

#include "i_entity_factory.hpp"


class EntityFactory : public IEntityFactory {
    std::shared_ptr<AEntity> createPlayer() override;
};

