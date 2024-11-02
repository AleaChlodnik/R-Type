/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** missile_component
*/

#pragma once

#include <cstdint>

/**
 * @struct PlayerMissileComponent
 * @brief Component that represents a missile belonging to a player.
 *
 * This component is used to identify missiles that are fired by players in the game.
 *
 * @var PlayerMissileComponent::playerId
 * The unique identifier of the player who fired the missile.
 */
struct PlayerMissileComponent {
    uint32_t playerId;
};