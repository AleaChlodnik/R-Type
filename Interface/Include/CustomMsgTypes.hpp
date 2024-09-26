/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once

#include <cstdint>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};