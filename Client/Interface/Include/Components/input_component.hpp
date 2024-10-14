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
    QUIT,
    NONE
};

struct InputComponent {
    InputType input;
};