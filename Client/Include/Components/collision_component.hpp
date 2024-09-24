/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** collision_component
*/
#include <SFML/Graphics.hpp>
#include "a_component.hpp"

#pragma once

namespace Components{

    class CollisionComponent : public AComponent {
    public:
        CollisionComponent(std::pair<float, float> size, std::pair<float, float> position); // origin is top left

        sf::RectangleShape getHitbox() const;
        void setHitbox(std::pair<float, float> size, std::pair<float, float> position);
        void setHitboxPosition(std::pair<float, float> position);
        std::pair<float, float> getHitboxPosition() const;
        void setHitboxSize(std::pair<float, float> size);
        std::pair<float, float> getHitboxSize() const ;

    private:
        sf::RectangleShape _hitbox;
    };

}
