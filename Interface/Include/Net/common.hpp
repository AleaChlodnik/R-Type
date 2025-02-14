/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netCommon
*/

#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

enum ServerStatus {
    WAITING,
    RUNNING,
    INITIALISATION,
    TRANSITION,
};