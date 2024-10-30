/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** error_handling
*/

#pragma once

#include <exception>

/**
 * @class componentNotFound
 * @brief Exception class for when a component is not found.
 *
 * This exception is thrown when a component is not found in the system.
 * It inherits from std::exception and overrides the what() method to provide
 * a custom error message.
 */
class componentNotFound : public std::exception {
    const char *what() const noexcept override { return "Component not found"; }
};

/**
 * @class entityNotFound
 * @brief Exception class for entity not found error.
 *
 * This exception is thrown when an entity is not found.
 * It is derived from the std::exception class.
 * The `what()` function is overridden to provide a custom error message.
 */
class entityNotFound : public std::exception {
    const char *what() const noexcept override { return "Entity not found"; }
};

/**
 * @class failedToLoadTexture
 * @brief Exception class for failed texture loading.
 *
 * This exception is thrown when there is a failure to load a texture.
 * It inherits from the std::exception class and overrides the what() method
 * to provide a custom error message.
 */
class failedToLoadTexture : public std::exception {
    const char *what() const noexcept override { return "Failed to load texture"; }
};

class failedToLoadSound : public std::exception {
    const char *what() const noexcept override { return "Failed to load sound"; }
};

class failedToLoadFont : public std::exception {
    const char *what() const noexcept override { return "Failed to load font"; }
};
