/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** error_handling
*/

#pragma once

#include <exception>

class componentNotFound : public std::exception {
    const char *what() const noexcept override
    {
        return "Component not found";
    }
};
