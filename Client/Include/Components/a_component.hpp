/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_component
*/

#pragma once

#include "i_component.hpp"

    class AComponent : public IComponent {
        public:
            virtual ~AComponent() override = default;

            std::string getType() const override { return _type; }
        
        private:
            std::string _type;
    };
