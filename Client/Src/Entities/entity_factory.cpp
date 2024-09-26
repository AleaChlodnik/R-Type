/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Entities/entity_factory.hpp"
#include "Components/components.hpp"
#include "Entities/entities.hpp"
#include "Entities/i_entity.hpp"

std::shared_ptr<IEntity> EntityFactory::createPlayer()
{
    auto player = std::make_shared<PlayerEntity>();

    player->addComponent(
        std::make_shared<HealthComponent>(player->getMaxHealth()));

    return player;
}
