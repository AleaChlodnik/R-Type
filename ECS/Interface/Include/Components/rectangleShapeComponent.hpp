/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** rectangleShapeComponent
*/

#pragma once
#include <SFML/Graphics.hpp>

struct RectangleShapeComponent {
    sf::RectangleShape rectangleShape;

    RectangleShapeComponent(sf::RectangleShape &rectangleShape)
    {
        this->rectangleShape = rectangleShape;
    }
};
