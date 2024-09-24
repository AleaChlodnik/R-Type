/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_component
*/

#pragma once

#include "i_component.hpp"

namespace Components {
    class AComponent : public IComponent {
        public:
            virtual ~AComponent() override = default;
    };
};
