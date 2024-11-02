/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ally_component
*/

#pragma once

/**
 * @struct LinkForceComponent
 * @brief Component that links an entity to a target entity by ID.
 *
 * This component is used to establish a link between the current entity and a target entity
 * identified by the targetId. This can be useful in scenarios where entities need to interact
 * or be aware of each other.
 *
 * @var LinkForceComponent::targetId
 * The ID of the target entity to which this entity is linked.
 *
 * @fn LinkForceComponent::LinkForceComponent(int _targetId)
 * @brief Constructs a LinkForceComponent with the specified target entity ID.
 * @param _targetId The ID of the target entity.
 */
struct LinkForceComponent {
    int targetId;

    LinkForceComponent(int _targetId) : targetId(_targetId) {}
};
