/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** texture_manager
*/

#pragma once

#include "error_handling.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager {
  public:
    sf::Texture &getTexture(const std::string &filePath)
    {
        auto it = textures.find(filePath);
        if (it != textures.end()) {
            return it->second;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            throw failedToLoadTexture();
        }

        textures[filePath] = std::move(texture);
        return textures[filePath];
    }

  private:
    std::unordered_map<std::string, sf::Texture> textures;
};
