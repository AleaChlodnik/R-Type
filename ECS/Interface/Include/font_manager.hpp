/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** font_manager
*/

#pragma once

#include "error_handling.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class FontManager {
  public:
    sf::Font &getFont(const std::string &filePath)
    {
        auto it = fonts.find(filePath);
        if (it != fonts.end()) {
            return it->second;
        }

        auto &font = fonts[filePath];
        if (!font.loadFromFile(filePath)) {
            fonts.erase(filePath);
            throw failedToLoadFont();
        }

        return fonts[filePath];
    }

    void releaseFont(const std::string &filePath) { fonts.erase(filePath); }

  private:
    std::unordered_map<std::string, sf::Font> fonts;
};
