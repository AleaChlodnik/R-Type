/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** missile_component
*/

#pragma once

#include <cstdint>

/**
 * @struct ForceMissileComponent
 * @brief Component representing a force missile in the ECS system.
 *
 * This component is used to identify and manage force missiles within the
 * Entity-Component-System (ECS) architecture.
 *
 * @var ForceMissileComponent::forceId
 * Unique identifier for the force missile.
 */
struct ForceMissileComponent {
    uint32_t forceId;
};