/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity
*/

#pragma once

#include <memory>
#include <vector>

#include "error_handling.hpp"

class Component;

class Entity {
    public:
        void addComponent(std::shared_ptr<Component> component);
	    template <typename T>
        std::shared_ptr<T> getComponent();

    private:
        std::vector<std::shared_ptr<Component>> components;
};
