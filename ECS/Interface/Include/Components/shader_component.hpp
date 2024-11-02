/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** shader_component
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

/**
 * @brief A component that holds a shader.
 *
 * This component is used to manage a shader in the ECS (Entity Component System).
 * It loads a shader from a file and stores it in a shared pointer.
 */
struct ShaderComponent {
    /**
     * @brief The shader object.
     *
     * This is a shared pointer to an sf::Shader object.
     */
    std::shared_ptr<sf::Shader> shader;

    /**
     * @brief Constructs a ShaderComponent and loads a shader from a file.
     *
     * @param path The file path to the shader.
     *
     * This constructor creates a new sf::Shader object and attempts to load
     * a shader from the specified file path. If the shader fails to load,
     * an error message is printed to the standard error stream.
     */
    ShaderComponent(std::string path)
    {
        shader = std::make_shared<sf::Shader>();
        if (!shader->loadFromFile(path, sf::Shader::Fragment)) {
            std::cerr << "Error loading shader" << std::endl;
        }
    }
};