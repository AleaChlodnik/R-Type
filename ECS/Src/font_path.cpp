/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** font_path
*/

#include <font_path.hpp>

std::string FontFactory(FontPath font)
{
    switch (font) {
    case FontPath::MAIN:
        return "Client/Assets/Fonts/GODOFWAR.TTF";
        break;
    default:
        return "";
        break;
    }
}
