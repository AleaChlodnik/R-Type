/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_entity
*/

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "error_handling.hpp"
#include "Components/components.hpp"
#include "i_entity.hpp"


class AEntity : public IEntity {
    public:
        virtual void addComponent(std::shared_ptr<AComponent> component) override { components.push_back(component); std::cout << "Component " << component->getType() << " added" << std::endl; }
        virtual std::vector<std::shared_ptr<AComponent>> getAllComponents() override { return components; }

        template <typename T>
        std::shared_ptr<T> getComponent()
        {
	        for (auto& component : components) {
                std::shared_ptr<T> comp = std::dynamic_pointer_cast<T>(component);
                if (comp != nullptr)
                    return comp;
            }
	        throw componentNotFound();
        }

    protected:
        std::vector<std::shared_ptr<AComponent>> components;
};



