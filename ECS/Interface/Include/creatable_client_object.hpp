
/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** creatable_client_object
*/

#pragma once

#include <cstdint>

/**
 * @enum CreatableClientObject
 * @brief Enum representing the types of client objects that can be created.
 *
 * This enum is used to specify the different types of objects that can be
 * instantiated on the client side in the R-Type game.
 *
 * @var CreatableClientObject::PLAYERMISSILE
 * Represents a missile fired by the player.
 *
 * @var CreatableClientObject::NONE
 * Represents the absence of a creatable client object.
 */
enum class CreatableClientObject : uint32_t
{
    PLAYERMISSILE,
    NONE
};
