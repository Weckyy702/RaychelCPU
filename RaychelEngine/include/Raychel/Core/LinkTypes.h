#ifndef RAYCHEL_LINKERTYPES_H
#define RAYCHEL_LINKERTYPES_H

#include "Types.h"

namespace Raychel {

#pragma region initializer classes

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

#pragma endregion

#pragma region Render classes

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

    struct ShadingData
    {

        vec3 hit_point, hit_normal;

    };

    struct RenderResult
    {
        color output;
    };

#pragma endregion

}

#endif // RAYCHEL_LINKERTYPES_H