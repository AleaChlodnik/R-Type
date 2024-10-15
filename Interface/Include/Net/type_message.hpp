
/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once

#include <cstdint>

/**
 * @file net_r_type_message.hpp
 * @brief Defines the TypeMessage enumeration for R-Type network messages.
 */
enum class TypeMessage : uint32_t
{
    /**
     * @brief Server accept message.
     *
     */
    ServerAccept,
    /**
     * @brief Server deny message.
     *
     */
    ServerDeny,
    /**
     * @brief Server ping message.
     *
     */
    ServerPing,
    /**
     * @brief Server pong message.
     *
     */
    MessageAll,
    /**
     * @brief Server message.
     *
     */
    ServerMessage,
    /**
     * @brief Server message.
     *
     */
    UpdateEntity,
    /**
     * @brief Client message.
     *
     */
    UpdateEntityResponse,
    /**
     * @brief Client connect message.
     *
     */
    ClientConnect,
    /**
     * @brief Client disconnect message.
     *
     */
    CreateEntityMessage,
    /**
     * @brief Client message.
     *
     */
    CreateEntityResponse,
    /**
     * @brief Client message.
     *
     */
    MoveEntityMessage,
    /**
     * @brief Client message.
     *
     */
    MoveEntityResponse,
    /**
     * @brief Client message.
     *
     */
    DestroyEntityMessage,
    /**
     * @brief Client message.
     *
     */
    DestroyEntityResponse,
    FinishInitialization,

};