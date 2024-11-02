/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** weapon_component
*/

#pragma once

#include <cstdint>

/**
 * @struct ForceWeaponComponent
 * @brief Represents a component for a force weapon in the game.
 *
 * This component is used to manage the state and properties of a force weapon
 * associated with a player.
 *
 * @var ForceWeaponComponent::playerId
 * The ID of the player who owns the force weapon.
 *
 * @var ForceWeaponComponent::level
 * The level of the force weapon.
 *
 * @var ForceWeaponComponent::attached
 * A flag indicating whether the force weapon is attached to the player.
 *
 * @fn ForceWeaponComponent::ForceWeaponComponent(uint32_t _playerId, uint32_t _level, uint32_t _attached)
 * @brief Constructs a new ForceWeaponComponent.
 *
 * @param _playerId The ID of the player who owns the force weapon.
 * @param _level The level of the force weapon.
 * @param _attached A flag indicating whether the force weapon is attached to the player.
 */
struct ForceWeaponComponent {
    uint32_t playerId;
    uint32_t level;
    bool attached;

    ForceWeaponComponent(uint32_t _playerId, uint32_t _level, uint32_t _attached)
        : playerId(_playerId), level(_level), attached(_attached)
    {
    }
};