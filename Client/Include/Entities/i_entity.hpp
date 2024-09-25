/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity
*/

#pragma once

#include <memory>
#include <vector>

class AComponent;



class IEntity {
    public:
        virtual void addComponent(std::shared_ptr<AComponent> component) = 0;
        virtual std::vector<std::shared_ptr<AComponent>> getAllComponents() = 0;
        virtual ~IEntity() {}
	    
        template <typename T>
        std::shared_ptr<T> getComponent();
};

