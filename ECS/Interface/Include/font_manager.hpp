/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** font_manager
*/

#pragma once

#include "error_handling.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/**
 * @class FontManager
 * @brief Manages the loading and retrieval of font resources.
 *
 * The FontManager class provides functionality to load, retrieve, and release
 * font resources. It maintains an internal storage of fonts, allowing for efficient
 * management and reuse of font resources.
 *
 * Example usage:
 * @code
 * FontManager fontManager;
 * sf::Font &font = fontManager.getFont("path/to/font.ttf");
 * // Use the font...
 * fontManager.releaseFont("path/to/font.ttf");
 * @endcode
 */
class FontManager {
  public:
    /**
     * @brief Retrieves a font from the font manager.
     *
     * This function attempts to find and return a font associated with the given file path.
     * If the font is not already loaded, it will attempt to load it from the specified file path.
     * If loading the font fails, an exception is thrown.
     *
     * @param filePath The path to the font file.
     * @return A reference to the loaded sf::Font object.
     * @throws failedToLoadFont if the font cannot be loaded from the specified file path.
     */
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

    /**
     * @brief Releases the font associated with the given file path.
     *
     * This function removes the font from the internal storage, effectively
     * releasing any resources associated with it.
     *
     * @param filePath The file path of the font to be released.
     */
    void releaseFont(const std::string &filePath) { fonts.erase(filePath); }

  private:
    /**
     * @brief A map that associates font names with their corresponding sf::Font objects.
     *
     * This unordered map uses strings as keys to store and retrieve sf::Font objects.
     * It allows for efficient lookup, insertion, and deletion of font resources by name.
     */
    std::unordered_map<std::string, sf::Font> fonts;
};
