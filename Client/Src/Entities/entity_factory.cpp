/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "i_entity.hpp"
#include "entities.hpp"
#include "components.hpp"
#include "entity_factory.hpp"

namespace Entities {
std::shared_ptr<IEntity> EntityFactory::createPlayer()
{
    auto player = std::make_shared<PlayerEntity>();

    auto healthComponent = std::make_shared<Components::HealthComponent>(player);
    
    player->addComponent(std::static_pointer_cast<AComponent>(healthComponent));

    return player;
}
};
