/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system
*/

#pragma once

class System {
    public:
        System() = default;
        virtual ~System() = default;
        virtual void update(float deltaTime) = 0;
};
