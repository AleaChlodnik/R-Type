/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** macro
*/

#pragma once

#define OK 0
#define ERROR_EPITECH 84
#define KO -1

#ifdef _WIN32_WINNT
    #define UNUSED [[maybe_unused]]
#endif
#ifndef _WIN32_WINNT
    #define UNUSED __attribute__((unused))
#endif
