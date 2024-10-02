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

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

namespace olc {
struct vf2d {
    float x, y;
};
} // namespace olc

struct sPlayerInformation {
    uint32_t nUniqueID = 0;
    uint32_t nAvatarID = 0;

    uint32_t nHealth = 100;
    uint32_t nAmmo = 20;
    uint32_t nKills = 0;
    uint32_t nDeaths = 0;

    float fRadius = 20;

    olc::vf2d vPos;
    olc::vf2d vVel;
};