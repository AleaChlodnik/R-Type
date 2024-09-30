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
#include "texture_manager.hpp"

class ComponentManager {
  public:
    // Usage ex: CMName.addComponent<NameOfComponent>(entityId, arg1, arg2);
    template <typename ComponentType, typename... Args>
    void addComponent(int entityId, Args &&...args)
    {
        ComponentType component(std::forward<Args>(args)...);
        components[typeid(ComponentType)][entityId] = std::make_any<ComponentType>(std::move(component));

        if constexpr (std::is_same_v<ComponentType, PositionComponent>) {
          auto spriteOpt = getComponent<SpriteComponent>(entityId);
          if (spriteOpt) {
              auto PositionOpt = getComponent<PositionComponent>(entityId);
              spriteOpt.value()->sprite.setPosition(PositionOpt.value()->x, PositionOpt.value()->y);
          }
        }
    }

    // Usage ex: auto componentName = CMName.getComponent<NameOfComponent>(entityId);
    template <typename ComponentType>
    std::optional<ComponentType*> getComponent(int entityId) {
        if (components.find(typeid(ComponentType)) != components.end()) {
            auto& entityComponents = components[typeid(ComponentType)];
            if (entityComponents.find(entityId) != entityComponents.end()) {
                return std::any_cast<ComponentType>(&entityComponents[entityId]);
            }
        }
        return std::nullopt; // Return nullopt if not found
    }

  private:
    // unordered map of <componentType, it's unordered map of <entityId, it's values for the componentType>>
    std::unordered_map<std::type_index, std::unordered_map<int, std::any>> components;
};
