/**
*\file LinkTypes.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Linking types
*\date 2021-03-24
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/
#ifndef RAYCHEL_LINKERTYPES_H
#define RAYCHEL_LINKERTYPES_H

#include "Types.h"

namespace Raychel {

#pragma region initializer classes

    /**
    *\brief Initialization data for renderable Objects
    *
    */
    struct ObjectData
    {
        Transform t;
        IMaterial_p mat{};
        //...
    };

    /**
    *\brief Initialization data for non-physical light sources
    *
    */
    struct LampData
    {

        color c;
        float b{0.0F};
        float sz{0.0F};
    };

#pragma endregion

#pragma region Render classes

    /**
     * \brief Options for the raymarching step in rendering.
     * 
     * \note The values in this struct can produce weird rendering results and
     *       should be left on default
     */
    struct RaymarchOptions
    {
        //maximum distance a ray can travel in the scene [m]
        float max_ray_distance = 50.0F;

        //maximum distance a point can be away form a surface while still being cosidered *on* the surface [m]
        float epsilon = 1e-5F;
    };

    /**
    *\brief Options for Postprocessing of rendered images
    *
    */
    struct PostprocessingOptions
    {
        bool do_postprocessing = false;
        bool do_denoising = false;
    };

    /**
    *\brief Options for the renderer
    *
    */
    struct RenderOptions : public RaymarchOptions, public PostprocessingOptions
    {
        bool doAA = false;
    };

    /**
    *\brief Precomputed data to accelerate raymarching
    *
    */
    struct RaymarchData
    {
        vec2 uv;
    };

    /**
    *\brief Data for lighting calculation. Most basic information needed for shading
    *
    */
    struct ShadingData
    {
        vec3 surface_point, hit_normal;
        vec3 in_direction;

        size_t recursion_depth{0};
    };

#pragma region Shading callback structs

    /**
    *\brief Data for simple shading. All Materials take this in
    *
    */
    struct PrimaryShadingData : ShadingData
    {
        size_t num_ray_steps{0};
        float ray_depth{0.0F};
    };

    /**
    *\brief Data for diffuse shading
    *
    */
    struct DiffuseShadingData : ShadingData
    {
        color albedo;
    };

    /**
    *\brief Data for reflective shading
    *
    */
    struct ReflectiveShadingData : ShadingData
    {
        color reflection_tint;
        float roughness{0.0F};
    };

#pragma endregion

    /**
    *\brief Info struct for objects that were hit while raymarching
    *
    */
    struct RaymarchHitInfo
    {
        PrimaryShadingData shading_data;
        not_null<IRaymarchable*> hit_object;
    };

    /**
    *\brief Data that leaves the rendering step. Can be used in Postprocessing
    *\todo add ray histograms for denoising via RHF
    */
    struct RenderResult
    {
        vec2 uv;
        color output;
    };

#pragma endregion

} // namespace Raychel

#endif // RAYCHEL_LINKERTYPES_H