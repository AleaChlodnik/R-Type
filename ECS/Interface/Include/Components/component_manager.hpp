/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** component_manager
*/

#pragma once

#include "components.hpp"
#include "texture_manager.hpp"
#include <any>
#include <iostream>
#include <memory>
#include <optional>
#include <typeindex>
#include <unordered_map>

/**
 * @class ComponentManager
 * @brief Manages the components of entities in an ECS system.
 *
 * The ComponentManager class provides functionality to add and retrieve components
 * for entities in an ECS system. It uses an unordered map to store the components,
 * where the key is the type of the component and the value is another unordered map
 * that maps entity IDs to their corresponding component values.
 */
class ComponentManager {
  public:
    // Usage ex: CMName.addComponent<NameOfComponent>(entityId, arg1, arg2);
    /**
     * @brief Adds a component to an entity.
     *
     * @tparam ComponentType The type of the component to add.
     * @tparam Args The types of the arguments to forward to the component's constructor.
     * @param entityId The ID of the entity to add the component to.
     * @param args The arguments to forward to the component's constructor.
     */
    template <typename ComponentType, typename... Args>
    void addComponent(int entityId, Args &&...args)
    {
        ComponentType component(std::forward<Args>(args)...);
        components[typeid(ComponentType)][entityId] =
            std::make_any<ComponentType>(std::move(component));
    }

    /**
     * Retrieves the component of the specified type associated with the given entity ID.
     *
     * @tparam ComponentType The type of the component to retrieve.
     * @param entityId The ID of the entity.
     * @return An optional pointer to the component if found, otherwise std::nullopt.
     */
    template <typename ComponentType> std::optional<ComponentType *> getComponent(int entityId)
    {
        if (components.find(typeid(ComponentType)) != components.end()) {
            auto &entityComponents = components[typeid(ComponentType)];
            if (entityComponents.find(entityId) != entityComponents.end()) {
                return std::any_cast<ComponentType>(&entityComponents[entityId]);
            }
        }
        return std::nullopt; // Return nullopt if not found
    }

    /**
     * @brief Retrieves the component map for the specified component type.
     *
     * @tparam ComponentType The type of the component.
     * @return std::optional<std::unordered_map<int, std::any>*> The component map if found, otherwise std::nullopt.
     */
    template <typename ComponentType>
    std::optional<std::unordered_map<int, std::any> *> getComponentMap()
    {
        auto it = components.find(typeid(ComponentType));
        if (it != components.end()) {
            return &it->second;
        }
        return std::nullopt;
    }

    template <typename ComponentType>
    void removeEntityFromComponent(int entityId)
    {
        auto it = components.find(typeid(ComponentType));
        if (it != components.end()) {
            auto &entityComponents = it->second;
            entityComponents.erase(entityId);
        }
    }

  private:
    // unordered map of <componentType, it's unordered map of <entityId, it's
    // values for the componentType>>
    /**
     * @brief A component manager that stores components in an unordered map.
     *
     * This component manager uses an unordered map to store components. The keys of the outer map are of type std::type_index, which represents the type of the component. The values of the outer map are inner unordered maps, where the keys are of type int and represent the entity ID, and the values are of type std::any, which allows storing components of any type.
     */
    std::unordered_map<std::type_index, std::unordered_map<int, std::any>> components;
};
