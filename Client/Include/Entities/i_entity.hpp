/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** i_entity
*/

#pragma once

class IEntity {
    public:
        virtual ~IEntity() = default;
        virtual int getId() const = 0;
};
