/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system
*/

#include "system.hpp"

void System::addEntity(std::shared_ptr<Entity> entity)
{
    entities.push_back(entity);
}
