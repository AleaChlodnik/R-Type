/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once

#include "netCommon.hpp"
#include <cstdint>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,

    Server_GetStatus,
    Server_GetPing,

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,
    Client_EntityReceveid,

    Game_AddEntity,
    Game_RemoveEntity,
    Game_UpdateEntity,
    Game_GetListEntities,
};