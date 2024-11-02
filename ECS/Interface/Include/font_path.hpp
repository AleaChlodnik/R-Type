/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** font_path
*/

#pragma once

#include <cstdint>
#include <string>

/**
 * @brief Enumeration of font paths.
 *
 * The FontPath enumeration contains a list of font paths that can be used to
 *
 * specify the location of a font resource. Each font path corresponds to a
 * specific font file that can be loaded and used by the application.
 *
 * Example usage:
 * @code
 * FontPath fontPath = FontPath::MAIN;
 * std::string font = FontFactory(fontPath);
 * @endcode
 *
 * @see FontFactory
 * @see operator<<
 * @see FontManager
 * @see FontPath
 *
 * @note The NONE font path is used to indicate that no font should be loaded.
 *
 */
enum class FontPath : uint32_t
{
    MAIN,
    NONE
};

/**
 * @brief Creates a font object from the given font path.
 *
 * This function takes a FontPath object and returns a string representation
 * of the font. The FontPath object should contain the necessary information
 * to locate and load the font.
 *
 * @param font The FontPath object containing the path to the font.
 * @return std::string The string representation of the font.
 */
std::string FontFactory(FontPath font);

/**
 * @brief Overloads the stream insertion operator to output the FontPath object.
 *
 * This function allows the FontPath object to be output to an ostream, such as
 * std::cout or any other output stream, by using the << operator.
 *
 * @param os The output stream to which the FontPath object will be written.
 * @param fontPath The FontPath object to be written to the output stream.
 * @return A reference to the output stream after the FontPath object has been written.
 */
std::ostream &operator<<(std::ostream &os, const FontPath &fontPath);
