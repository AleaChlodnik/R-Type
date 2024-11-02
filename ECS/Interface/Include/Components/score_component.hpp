/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** score_component
*/

#pragma once

/**
 * @file score_component.hpp
 * @brief Defines the ScoreComponent struct used to store the score of an entity.
 */

/**
 * @struct ScoreComponent
 * @brief Component that holds the score of an entity.
 *
 * The ScoreComponent is used within the ECS framework to keep track of the score
 * associated with a particular entity.
 */
struct ScoreComponent {
    int score;
};