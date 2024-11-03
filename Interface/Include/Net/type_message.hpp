
/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once

#include <cstdint>

/**
 * @enum TypeMessage
 * @brief Enumeration for different types of network messages in R-Type.
 *
 * This enumeration defines various message types used for communication
 * between the server and clients in the R-Type game.
 *
 * @var TypeMessage::ServerAccept
 * Server accept message.
 *
 * @var TypeMessage::ServerDeny
 * Server deny message.
 *
 * @var TypeMessage::ServerPing
 * Server ping message.
 *
 * @var TypeMessage::MessageAll
 * Server pong message.
 *
 * @var TypeMessage::ServerMessage
 * Server message.
 *
 * @var TypeMessage::UpdateEntity
 * Server message.
 *
 * @var TypeMessage::UpdateEntityResponse
 * Client message.
 *
 * @var TypeMessage::ClientConnect
 * Client connect message.
 *
 * @var TypeMessage::CreateEntityMessage
 * Client disconnect message.
 *
 * @var TypeMessage::CreateEntityResponse
 * Client message.
 *
 * @var TypeMessage::MoveEntityMessage
 * Client message.
 *
 * @var TypeMessage::MoveEntityResponse
 * Client message.
 *
 * @var TypeMessage::DestroyEntityMessage
 * Client message.
 *
 * @var TypeMessage::DestroyEntityResponse
 * Client message.
 *
 * @var TypeMessage::AnimateEntityMessage
 * Client message.
 *
 * @var TypeMessage::AnimateEntityResponse
 * Client message.
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
    PlayerInformation,
    /**
     * @brief Server message.
     *
     */
    UpdateEntity,
    /**
     * @brief Server message.
     *
     */
    GameBarInformation,
    /**
     * @brief Server message.
     *
     */
    GameTransitionMode,
    /**
     * @brief Server message.
     *
     */
    IsPlayerReady,

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
    /**
     * @brief Client message.
     *
     */
    FinishInitialization,
    /**
     * @brief Client message.
     *
     */
    AnimateEntityMessage,


    /**
     * @brief Client message.
     *
     */
    PlayerInformationResponse,
    /**
     * @brief Client message.
     *
     */
    UpdateInfoBar,
    /**
     * @brief Client message
     *
     */
    GameBarInformationResponse,
    /**
     * @brief Client message
     *
     */
    GameParametersInformation,
    /**
     * @brief Client message
     *
     */
    GameEntityInformation,
    /**
     * @brief Client message
     *
     */
    GameTransitionModeResponse,
    /**
     * @brief Client message
     *
     */
    PlayerReady,
    /**
     * @brief Client message
     *
     */
    EndOfGame,
};

enum class PlayerMovement : uint32_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};