/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_component
*/

#pragma once

#include <string>

#include "error_handling.hpp"


class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual std::string getType() const = 0;

    private:
        std::string _type;
};

