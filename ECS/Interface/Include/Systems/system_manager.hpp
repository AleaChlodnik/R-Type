/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system_manager
*/

#pragma once

#include "i_system.hpp"
#include "systems.hpp"

class SystemManager {
  public:
    void addSystem(std::shared_ptr<ISystem> system) { systems.push_back(system); }

    void updateSystems(float deltaTime)
    {
        for (const auto &system : systems) {
            system->update(deltaTime);
        }
    }

  private:
    std::vector<std::shared_ptr<ISystem>> systems;
};
