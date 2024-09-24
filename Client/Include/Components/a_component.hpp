/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_component
*/

#pragma once

#include "error_handling.hpp"
#include "i_component.hpp"

class AComponent : public IComponent {
    public:
        virtual ~AComponent() override = default;
};
