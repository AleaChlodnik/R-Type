/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** background_component
*/

#pragma once

struct BackgroundComponent {
    float speed;
    float position;

    BackgroundComponent(float speed, float position)
    {
        this->speed = speed;
        this->position = position;
    }
};
