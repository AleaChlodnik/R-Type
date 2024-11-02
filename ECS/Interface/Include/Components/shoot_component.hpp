/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** shoot_component
*/

#pragma once

#include <chrono>

/**
 * @struct ShootComponent
 * @brief Component that handles shooting mechanics for an entity.
 *
 * This component keeps track of the next allowed shooting time, the cooldown
 * period between shots, and whether the entity can shoot.
 *
 * @var ShootComponent::nextShootTime
 * The time point when the entity is next allowed to shoot.
 *
 * @var ShootComponent::cooldownTime
 * The cooldown duration between consecutive shots.
 *
 * @var ShootComponent::canShoot
 * A flag indicating whether the entity is currently allowed to shoot.
 *
 * @fn ShootComponent::ShootComponent(std::chrono::milliseconds cooldown)
 * @brief Constructs a ShootComponent with a specified cooldown time.
 *
 * Initializes the nextShootTime to the current time and sets the cooldownTime
 * to the provided value.
 *
 * @param cooldown The cooldown duration between consecutive shots.
 */
struct ShootComponent {
    std::chrono::system_clock::time_point nextShootTime;
    std::chrono::milliseconds cooldownTime;
    bool canShoot;

    ShootComponent(std::chrono::milliseconds cooldown)
        : nextShootTime(std::chrono::system_clock::now()), cooldownTime(cooldown)
    {
    }
};
