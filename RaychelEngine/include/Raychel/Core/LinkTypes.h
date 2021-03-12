/*
*   
*   Helper Classes to pass between the different modules of the RaymarchController
*   Should all be POD types
*/

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
        vec2 uv;
    };

    struct RemarchRequest
    {
        vec3 p, dir;

        size_t recurstion_depth;
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
        color output;
    };

}