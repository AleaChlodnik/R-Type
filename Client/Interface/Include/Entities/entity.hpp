/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity
*/

#pragma once

#include "i_entity.hpp"

class Entity : public IEntity {
  public:
    explicit Entity(int id) : _id(id) {}
    int getId() const { return _id; }

  private:
    int _id;
};
