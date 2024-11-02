/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game_struct
*/

#pragma once

/**
 * @brief GameState enum.
 *
 * This enum contains the different State of the game.
 */

enum class GameState
{
    Menu,
    LevelOne,
    LevelTwo,
    LevelThree,
    LevelFour,
};

/**
 * @brief Game parameters struct.
 *
 * This struct contains the parameters for the game, such as the number of basic monsters, the
 * spawn time (on second) for basic monsters, the number of shooter enemies, the spawn time (on
 * second) for shooter enemies, and the game state.
 */

struct GameParameters {
    int nbrOfBasicMonster;
    int spawnTimeBasicMonster;

    int nbrOfShooterEnemy;
    int spawnTimeShooterEnemy;

    GameState levelType;
};
