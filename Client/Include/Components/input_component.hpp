/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** input_component
*/

#pragma once

enum class InputType
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SHOOT,
    PAUSE,
    QUIT,
    NONE
};

struct InputComponent {
    InputType input;
};