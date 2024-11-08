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

/**
 * @class failedToLoadSound
 * @brief Exception class for handling sound loading failures.
 *
 * This exception is thrown when the application fails to load a sound file.
 * It inherits from std::exception and overrides the what() method to provide
 * a specific error message.
 */
class failedToLoadSound : public std::exception {
    const char *what() const noexcept override { return "Failed to load sound"; }
};

/**
 * @class failedToLoadFont
 * @brief Exception class for handling font loading failures.
 *
 * This exception is thrown when the application fails to load a font.
 * It inherits from std::exception and overrides the what() method to
 * provide a specific error message.
 */
class failedToLoadFont : public std::exception {
    const char *what() const noexcept override { return "Failed to load font"; }
};

/**
 * @class playerIdNotFound
 * @brief Exception class for handling cases where a player ID is not found.
 *
 * This exception is thrown when a requested player ID cannot be found in the system.
 * It inherits from the standard std::exception class and overrides the what() method
 * to provide a specific error message.
 */
class playerIdNotFound : public std::exception {
    const char *what() const noexcept override { return "Player ID not found"; }
};

/**
 * @class failedToCreateFile
 * @brief Exception class for handling file creation failures.
 *
 * This exception is thrown when a file creation operation fails.
 * It inherits from the standard std::exception class.
 */
class failedToCreateFile : public std::exception {
    const char *what() const noexcept override { return "Failed to create file"; }
};

/**
 * @class failedToOpenFile
 * @brief Exception class for handling file opening failures.
 *
 * This exception is thrown when a file cannot be opened.
 * It inherits from std::exception and overrides the what() method
 * to provide a specific error message.
 */
class failedToOpenFile : public std::exception {
    const char *what() const noexcept override { return "Failed to open file"; }
};
