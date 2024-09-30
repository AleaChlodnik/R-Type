/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** component_manager
*/

#pragma once

#include "components.hpp"
#include <any>
#include <iostream>
#include <memory>
#include <optional>
#include <typeindex>
#include <unordered_map>

class ComponentManager {
  public:
    // Usage ex: CMName.addComponent<NameOfComponent>(entityId, arg1, arg2);
    template <typename ComponentType, typename... Args>
    void addComponent(int entityId, Args &&...args)
    {
        ComponentType component(std::forward<Args>(args)...);
        components[typeid(ComponentType)][entityId] =
            std::make_any<ComponentType>(std::move(component));
    }

    // Usage ex: auto componentName =
    // CMName.getComponent<NameOfComponent>(entityId);
    template <typename ComponentType> std::optional<ComponentType> getComponent(int entityId)
    {
        auto it = components.find(typeid(ComponentType));
        if (it != components.end() && it->second.find(entityId) != it->second.end()) {
            return std::any_cast<ComponentType>(it->second[entityId]);
        }
        return std::nullopt;
    }

  private:
    // unordered map of <componentType, it's unordered map of <entityId, it's
    // values for the componentType>>
    std::unordered_map<std::type_index, std::unordered_map<int, std::any>> components;
};
