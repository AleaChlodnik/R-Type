/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ally_component
*/

#pragma once

#include <Entities/entity.hpp>
#include <memory>

struct LinkForceComponent {
    int targetId;

    LinkForceComponent(int _targetId) : targetId(_targetId) {}
};
