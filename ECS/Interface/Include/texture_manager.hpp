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
    /**
     *  @brief Retrieves a texture from the texture manager.
     *
     * This function attempts to find the texture associated with the given file path in the
     * texture manager. If the texture is found, it is returned. Otherwise, a new texture is loaded
     * from the file path and added to the texture manager before being returned.
     *
     * @throws failedToLoadTexture If the texture fails to load from the file path.
     *
     * @param filePath The file path of the texture to retrieve.
     * @return sf::Texture&  A reference to the retrieved texture.
     */
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
    /**
     * @brief A container for storing textures with string keys.
     *
     * This unordered map allows you to associate a string key with an sf::Texture object.
     * It provides fast access to textures based on their keys.
     */
    std::unordered_map<std::string, sf::Texture> textures;
};
