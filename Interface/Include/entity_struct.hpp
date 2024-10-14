/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entities_struct
*/

#include <cstdint>
#ifndef ENTITIES_STRUCT_HPP_
    #define ENTITIES_STRUCT_HPP_

struct vf2d {
    float x = 0;
    float y = 0;
};

struct hbf2d {
    float width = 0;
    float height = 0;
};

struct EntityInformation {
    uint32_t uniqueID = 0;
    uint32_t spriteID = 0;

    uint32_t nPoint = 0;
    uint32_t nDeaths = 0;

    uint32_t Ping = 0;

    hbf2d hitbox;
    vf2d vPos;
};

#endif /* !ENTITIES_STRUCT_HPP_ */
