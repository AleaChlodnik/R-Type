/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** score_component
*/
#include "Components/score_component.hpp"

ScoreComponent::ScoreComponent(int score) { _score = score; }

void ScoreComponent::setScore(int score) { _score = score; }

int ScoreComponent::getScore() const { return _score; }

int ScoreComponent::operator+(int score)
{
    _score += score;
    return _score;
}
