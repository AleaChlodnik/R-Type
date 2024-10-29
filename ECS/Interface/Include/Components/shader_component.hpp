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

struct ShaderComponent {
    std::shared_ptr<sf::Shader> shader;

    ShaderComponent(std::string path)
    {
        shader = std::make_shared<sf::Shader>();
        if (!shader->loadFromFile(path, sf::Shader::Fragment)) {
            std::cerr << "Error loading shader" << std::endl;
        }
    }
};