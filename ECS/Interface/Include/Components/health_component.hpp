/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** health_component
*/

#pragma once

/**
 * @struct HealthComponent
 * @brief Represents the health attributes of an entity.
 *
 * This component is used to store and manage the health-related data of an entity.
 *
 * @var HealthComponent::max_health
 * Maximum health value that the entity can have.
 *
 * @var HealthComponent::health
 * Current health value of the entity.
 */
struct HealthComponent {
    int max_health;
    int health;
};
