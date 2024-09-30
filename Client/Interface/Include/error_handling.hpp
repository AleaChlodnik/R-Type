/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** error_handling
*/

#pragma once

#include <exception>

class componentNotFound : public std::exception {
    const char *what() const noexcept override { return "Component not found"; }
};

class entityNotFound : public std::exception {
    const char *what() const noexcept override { return "Entity not found"; }
};

class failedToLoadTexture : public std::exception {
    const char *what() const noexcept override { return "Failed to load texture"; }
};
