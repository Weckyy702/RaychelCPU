/**
*\file lights.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for lamp classes
*\date 2021-06-25
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
#ifndef RAYCHEL_LIGHTS_H
#define RAYCHEL_LIGHTS_H

#include "Interface.h"
    
namespace Raychel {

    class DirectionalLight : public Lamp
    {
        public:

        DirectionalLight(const LampData& data, vec3 direction)
            :Lamp{data}, direction_{direction}
        {}

        [[nodiscard]] color get_lighting(const vec3& /*unused*/) const noexcept override
        {
            return lampColor();
        }

        [[nodiscard]] vec3 get_light_vector(const vec3& /*unused*/) const noexcept override
        {
            return direction_ * -10'000.0F; //a directional light is 'infinitely' far away
        }

        private:
            vec3 direction_;
    };

}

#endif //!RAYCHEL_LIGHTS_H