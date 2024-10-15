#include <cstdint>
#include <spriteData.hpp>
#ifndef ENTITIES_STRUCT_HPP_
    #define ENTITIES_STRUCT_HPP_

struct vf2d {
    float x = 0;
    float y = 0;
};

struct EntityInformation {
    uint32_t uniqueID = 0;
    SpriteData_t spriteData;
    vf2d vPos;
};

#endif /* !ENTITIES_STRUCT_HPP_ */
