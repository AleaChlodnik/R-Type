/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Components/components.hpp"
#include "Entities/entities.hpp"
#include "Entities/entity_factory.hpp"

std::shared_ptr<AEntity> EntityFactory::createPlayer()
{
    std::shared_ptr<AEntity> player = std::make_shared<PlayerEntity>();
    std::shared_ptr<AComponent> health = std::make_shared<HealthComponent>(100);
    player->addComponent(health);

    //auto player = std::make_shared<PlayerEntity>();
    //player->addComponent(std::make_shared<HealthComponent>(100));
    //player->addComponent(std::make_shared<SpriteComponent>("Assets/temp_player.png", std::make_pair(2, 2), std::make_pair(0, 0)));

    return player;
}

