/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** score_component
*/
#include "../../Include/Components/score_component.hpp"

Components::ScoreComponent::ScoreComponent(int score)
{
    _score = score;
}

void Components::ScoreComponent::setScore(int score)
{
    _score = score;
}

int Components::ScoreComponent::getScore() const
{
    return _score;
}

int Components::ScoreComponent::operator+(int score)
{
    _score += score;
    return _score;
}
