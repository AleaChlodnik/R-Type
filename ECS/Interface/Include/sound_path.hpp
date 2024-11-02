/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sound_path
*/

#pragma once

#include <cstdint>
#include <string>

/**
 *
 * This header file defines the ActionType enumeration and declares the
 * SoundFactory function.
 *
 * ActionType:
 * An enumeration representing different types of actions that can trigger
 * sounds in the game. The possible values are:
 * - Win: Represents a winning action.
 * - Shot: Represents a shooting action.
 * - Boss: Represents a boss-related action.
 * - PowerUp: Represents a power-up action.
 * - GameOver: Represents a game over action.
 * - BossDeath: Represents a boss death action.
 * - Explosion: Represents an explosion action.
 * - Background: Represents background music or sound.
 * - NONE: Represents no action.
 *
 * SoundFactory:
 * A function that takes an ActionType as a parameter and returns a string
 * representing the path to the corresponding sound file.
 *
 * @param action The ActionType for which the sound path is required.
 * @return A string representing the path to the sound file corresponding to
 * the given action.
 */
enum class ActionType : uint32_t
{
    Win,
    Shot,
    Boss,
    PowerUp,
    GameOver,
    BossDeath,
    Explosion,
    Background,
    NONE,
};

/**
 * @brief Generates the file path for a sound based on the given action type.
 *
 * This function takes an ActionType enumeration value and returns a corresponding
 * file path as a string. The file path points to the sound file associated with
 * the specified action.
 *
 * @param action The action type for which the sound file path is needed.
 * @return std::string The file path of the sound associated with the given action.
 */
std::string SoundFactory(ActionType action);
