/**
*\file Camera.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Camera class
*\date 2021-03-25
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
#ifndef RAYCHEL_CAMERA_H
#define RAYCHEL_CAMERA_H

#include <array>
#include "Raychel/Core/Types.h"

namespace Raychel {

    /**
    *\brief Freely orientable Camera used for rendering.
    *
    */
    class Camera {

    public:

        Camera()=default;

        Camera(const Transform& _t, float _zoom)
            :transform_(_t), zoom_(_zoom)
        {}

        vec3 forward() const noexcept;

        vec3 right() const noexcept;

        vec3 up() const noexcept;

        inline float zoom() const noexcept
        {
            return zoom_;
        }


        void setRoll(float angle) noexcept;

        void setPitch(float angle) noexcept;

        void setYaw(float angle) noexcept;

        Quaternion updateRoll(float da) noexcept;

        Quaternion updatePitch(float da) noexcept;

        Quaternion updateYaw(float da) noexcept;
        
        friend class RaymarchRenderer;

    private:

            Transform transform_;
            float zoom_=1.0;

            //float exposure;

            //colors that each channel reacts to. Essential for color bleed etc.
            std::array<color, 3> color_channels_ = {
                color(1, 0, 0),
                color(0, 1, 0),
                color(0, 0, 1)
            };
    };

}

#endif //RAYCHEL_CAMERA_H