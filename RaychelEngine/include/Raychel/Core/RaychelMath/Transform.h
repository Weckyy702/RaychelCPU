/**
*\file Transform.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Transforms
*\date 2021-03-23
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
#ifndef RAYCHEL_TRANSFORM_H
#define RAYCHEL_TRANSFORM_H

#pragma once

#include "../utils.h"
#include "vec3.h"
#include "Quaternion.h"

namespace Raychel
{
    
    /**
    *\brief An (almost) mathematical transform (scale is missing)
    *
    *\tparam _number Type of the Transform. Must be arithmetic
    */
    template<RAYCHEL_NUMBER _number>
    struct TransformImp
    {

        //this ugly mess will have to stay until C++20
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

    private:

        RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::vec3<T> requires T to be of arithmetic type!");
        using vec3 = vec3Imp<value_type>;
        using Quaternion = QuaternionImp<value_type>;
    
    public:

        TransformImp()=default;

        TransformImp(const vec3& pos)
            :position{ pos }
        {}

        TransformImp(const Quaternion& rot)
            :rotation{ rot }
        {}

        TransformImp(const vec3& pos, const Quaternion& rot)
            :position{ pos }, rotation( rot )
        {}

        vec3 apply(const vec3&) const;

        /**
        *\brief Convert the transform to another transform of type To
        *
        *\tparam To Type of the converted Transform
        *\return TransformImp<T> 
        */
        template<typename To>
        constexpr TransformImp<To> to() const noexcept;

        vec3 position;
        Quaternion rotation;

    };

}


#endif //RAYCHEL_TRANSFORM_H