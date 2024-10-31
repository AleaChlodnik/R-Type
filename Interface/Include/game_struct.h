/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game_struct
*/

#pragma once

/**
 * @brief TypeLevel enum.
 *
 * This enum contains the different levels of the game.
 */

enum class TypeLevel
{
    LevelOne,
    LevelTwo,
    LevelThree,
    LevelFour,
};

/**
 * @brief Game parameters struct.
 *
 * This struct contains the parameters for the game, such as the number of basic monsters, the spawn
 * time (on second) for basic monsters, the number of shooter enemies, the spawn time (on second) for shooter enemies, and
 * the level type.
 */

struct GameParameters {
    int nbrOfBasicMonster;
    int spawnTimeBasicMonster;

    int nbrOfShooterEnemy;
    int spawnTimeShooterEnemy;

    TypeLevel levelType;
};

