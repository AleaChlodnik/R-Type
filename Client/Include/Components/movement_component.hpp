/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** movement_component
*/
#include <iostream>
#include "a_component.hpp"

#pragma once

namespace Components {

    class MovementComponent : public AComponent{
        public:
            MovementComponent() = default;
            MovementComponent(std::pair<float, float> speed, std::pair<float, float> direction);

            void setSpeed(std::pair<float, float> speed);
            std::pair<float, float> getSpeed() const;
            void setDirection(std::pair<float, float> direction);
            std::pair<float, float> getDirection() const;

        private:
            std::pair<float, float> _speed;
            std::pair<float, float> _direction;
    };

}
