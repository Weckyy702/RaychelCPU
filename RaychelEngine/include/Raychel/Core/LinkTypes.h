#ifndef RAYCHEL_LINKERTYPES_H
#define RAYCHEL_LINKERTYPES_H

#include "Types.h"

namespace Raychel {

    struct ObjectData
    {
        Transform t;
        //...
    };

    struct LampData
    {

        color c;
        double b;
        double sz;

    };

    struct RaymarchRequest
    {
        vec3 origin, direction;

        size_t recursionDepth;
    };

    struct RaymarchHitData
    {

        vec3 hit_point;
        size_t obj_index;
        bool did_hit; //did the ray hit an object or "the sky"?

    };

    struct HitData
    {

        vec3 hit_point, hit_normal;

    };

    struct RenderResult
    {
        vec3 output;
    };

}

#endif // RAYCHEL_LINKERTYPES_H