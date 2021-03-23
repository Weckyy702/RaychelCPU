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

    /**
     * \brief Options for the raymarching step in rendering.
     * 
     * \note The values in this struct can produce weird rendering results and
     *       should be left on default
     */
    struct RaymarchOptions {
        double _epsilon = 1e-6;
        double _normalBias = _epsilon*0.1;
        double _surfaceBias = _epsilon * 5;
    };

    struct PostprocessingOptions {
        bool doPostprocessing = false;
        bool doDenoising = false;
    };

    struct RenderOptions : public RaymarchOptions, public PostprocessingOptions
    {
        bool doAA = false;
    };

    struct RaymarchRequest
    {
        vec2 uv;
    };

    struct ShadingData
    {

        vec3 hit_point, hit_normal;
        size_t num_ray_steps;
        double ray_depth;

    };

    struct RenderResult
    {
        vec2 uv;
        color output; //actually color output
    };

#pragma endregion

}

#endif // RAYCHEL_LINKERTYPES_H