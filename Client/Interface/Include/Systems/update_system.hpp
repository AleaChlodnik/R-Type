/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update_system
*/

#pragma once

#include "Components/component_manager.hpp"
#include "Components/components.hpp"
#include "Entities/entity_manager.hpp"

class UpdateSystem {
  public:
    UpdateSystem();

    // void positions(EntityManager &entityManager, ComponentManager &componentManager)
    // {
    //     const auto &entities = entityManager.getAllEntities();
    //     for (const auto &entity : entities) {
    //         auto currPos = componentManager.getComponent<PositionComponent>(entity.getId());
    //         componentManager.addComponent<PositionComponent>(entity.getId(), currPos.value()->x
    //         + 1, currPos.value()->y);
    //     }
    // }
};
