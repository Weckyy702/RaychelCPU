/**
*\file Interface.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Interface header for Lamp classes
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
#ifndef RAYCHEL_LIGHT_INTERFACE_H
#define RAYCHEL_LIGHT_INTERFACE_H

#include "Raychel/Core/LinkTypes.h"

namespace Raychel {

    struct ILamp
    {
        RAYCHEL_MAKE_NONCOPY_NONMOVE(ILamp);

        ILamp() = default;

        /**
        *\brief Calculate the lamps lighting onto surface point, disregarding the lambertian term
        *
        *\param surface_point the surface point that the lamp shines upon
        *\return color lighting color for surface_point
        */
        [[nodiscard]] virtual color get_lighting(const vec3& surface_point) const noexcept = 0;

        /**
        *\brief Get the (non-normalized!) vector pointing from surface_point to the lamp
        *
        *\param surface_point Origin of the vector returned
        *\return vec3 The vector that connects surface_point and the lamp
        */
        [[nodiscard]] virtual vec3 get_light_vector(const vec3& surface_point) const noexcept = 0;

        /**
        *\brief Get the size of the lamp. Used for smooth lighting calculations
        *
        *\return float size of the lamp
        */
        [[nodiscard]] virtual float get_size() const noexcept = 0;

        virtual ~ILamp() = default;
    };

    class Lamp : public ILamp
    {
    public:
        RAYCHEL_MAKE_NONCOPY_NONMOVE(Lamp);

        [[nodiscard]] float get_size() const noexcept override
        {
            return size_;
        }

    protected:
        explicit Lamp(const LampData& _data) : color_{_data.c}, brightness_{_data.b}, size_{_data.sz}
        {}

        [[nodiscard]] color lampColor() const noexcept
        {
            return color_;
        }
        [[nodiscard]] float brightness() const noexcept
        {
            return brightness_;
        }
        [[nodiscard]] float size() const noexcept
        {
            return size_;
        }

        ~Lamp() override = default;

    private:
        color color_;
        float brightness_{1.0};
        float size_{0.0};
    };

} // namespace Raychel

#endif //!RAYCHEL_LIGHT_INTERFACE_H