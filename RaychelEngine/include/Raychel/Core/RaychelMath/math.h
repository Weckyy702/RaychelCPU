/**
*\file math.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Main include header for RaychelMath library
*\date 2021-06-15
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
#ifndef RAYCHEL_MATH_H
#define RAYCHEL_MATH_H

#include <type_traits>
#include "Raychel/Core/Raychel_assert.h"

namespace Raychel {

    using std::size_t;

    template <typename _num>
    struct vec2Imp;
    template <typename _num>
    struct vec3Imp;
    template <typename _num>
    struct colorImp;
    /*TODO: implement
	template<typename _num>
	class colorAlphaImp;
	*/
    template <typename _num>
    class QuaternionImp;
    template <typename _num>
    struct TransformImp;

    template <typename _number>
    constexpr _number sq(_number x)
    {
        static_assert(std::is_arithmetic_v<_number>, "Raychel::sq<T> requires T to be of arithmetic type!");
        return x * x;
    }

    /**
	*\brief Linearly interpolate between two numbers
	*
	*\tparam _number Type of number to interpolate. Must be arithmetic
	*\param a first number (x=0.0)
	*\param b second number (x=1.0)
	*\param x value of interpolation
	*\return _number the interpolated number
	*/
    template <typename _number>
    constexpr _number lerp(_number a, _number b, long double x)
    {
        return (x * b) + ((1.0 - x) * a);
    }

    template <typename _integral>
    constexpr _integral bit(size_t shift)
    {
        static_assert(std::is_integral_v<_integral>, "Raychel::bit<T> requires T to be of integral type!");
        RAYCHEL_ASSERT(shift < (sizeof(_integral) * 8));
        return static_cast<_integral>(1U << shift);
    }

    /**
	*\brief Get number of digits in a number
	*
	*\param num The number with its digits
	*\return constexpr int 
	*/
    constexpr int numDigits(unsigned long long num, unsigned int base = 10U)
    {
        int digits = 0;

        do {
            digits++;
            num /= base;
        } while (num != 0);

        return digits;
    }

} // namespace Raychel
#endif //!RAYCHEL_MATH_H