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
        IMaterial* mat;
        //...
    };
    /**
    *\brief Initialization data for non-physical light sources
    *
    */
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

    /**
    *\brief Options for Postprocessing of rendered images
    *
    */
    struct PostprocessingOptions {
        bool doPostprocessing = false;
        bool doDenoising = false;
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
    *\brief Data for lighting calculation. All Materials take this in
    *
    */
    struct ShadingData
    {

        vec3 hit_point, hit_normal;
        size_t num_ray_steps;
        double ray_depth;

    };

    /**
    *\brief Data that leaves the rendering step. Can be used in Postprocessing
    *
    */
    struct RenderResult
    {
        vec2 uv;
        color output;
    };

#pragma endregion

}

#endif // RAYCHEL_LINKERTYPES_H