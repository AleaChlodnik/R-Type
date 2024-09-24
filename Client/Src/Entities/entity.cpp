/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity
*/

#include "entity.hpp"

void Entity::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}

template <typename T>
std::shared_ptr<T> Entity::getComponent()
{
    std::shared_ptr<T> comp;

	for (auto &component : components) {
        comp = std::dynamic_pointer_cast<T>(component);
		if (comp != nullptr)
			return comp;
	}
	throw componentNotFound();
}
