/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity
*/

#pragma once

class Entity {
    public:
        explicit Entity(int id) : _id(id) {}
        int getId() const { return _id; }

    private:
        int _id;
};
