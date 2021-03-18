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
    };

    struct ShadingData
    {

        vec3 hit_point, hit_normal;
        size_t num_ray_steps;
        double ray_depth;

    };

    struct RenderResult
    {
        color output;
    };

#pragma endregion

}

#endif // RAYCHEL_LINKERTYPES_H