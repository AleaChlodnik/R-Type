/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** rectangleShapeComponent
*/

#pragma once
#include <SFML/Graphics.hpp>

/**
 * @struct RectangleShapeComponent
 * @brief A component that holds an sf::RectangleShape.
 *
 * This component is used to store and manage an sf::RectangleShape object.
 */
struct RectangleShapeComponent {
    sf::RectangleShape rectangleShape;

    /**
     * @brief Constructs a new RectangleShapeComponent.
     *
     * @param rectangleShape A reference to an sf::RectangleShape object.
     */
    RectangleShapeComponent(sf::RectangleShape &rectangleShape)
    {
        this->rectangleShape = rectangleShape;
    }
};
