/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game_text
*/

#pragma once

#include <cstdint>
#include <string>

/**
 * @enum GameText
 * @brief Enumeration for different types of game text.
 *
 * This enumeration defines the different types of text that can be displayed in the game.
 */
enum class GameText : uint32_t
{
    Lives, /**< Represents the number of lives left. */
    Score, /**< Represents the player's score. */
    NONE,  /**< Represents no text. */
};

/**
 * @brief Factory function to convert GameText enum to a string.
 *
 * @param text The GameText enum value.
 * @return A string representation of the GameText value.
 */
std::string GameTextFactory(GameText text);

/**
 * @brief Overloaded stream insertion operator for GameText.
 *
 * @param os The output stream.
 * @param text The GameText enum value.
 * @return The output stream with the GameText value inserted.
 */
std::ostream &operator<<(std::ostream &os, const GameText &text);
