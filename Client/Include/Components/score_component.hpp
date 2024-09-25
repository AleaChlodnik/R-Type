/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** score_component
*/
#include "a_component.hpp"
#pragma once


    class ScoreComponent: public AComponent{
        public:
            ScoreComponent() = default;
            ScoreComponent(int score);
            
            void setScore(int score);
            int getScore() const;

            int operator+(int score);
        private:
            int _score;
            const std::string _type = "score";
    };


