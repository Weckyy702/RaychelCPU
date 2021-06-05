/**
*\file equivalent.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for the equivalent<> function template
*\date 2021-06-05
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
#ifndef RAYCHEL_EQUIVALENT_H
#define RAYCHEL_EQUIVALENT_H

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace Raychel {

    namespace details {

        template <typename T, std::size_t fac>
        struct _epsilon_helper_base
        {
            static_assert(std::is_floating_point_v<T>);
            static constexpr T value = fac * std::numeric_limits<T>::epsilon();
        };

        /**
        *\brief Helper struct to find correct epsilon values for the different floating point numbers
        *
        *\tparam T 
        */
        template <typename T>
        struct epsilon_helper
        {};

        template <>
        struct epsilon_helper<float> : _epsilon_helper_base<float, 50>
        {};

        template <>
        struct epsilon_helper<double> : _epsilon_helper_base<double, 25>
        {};

        template <>
        struct epsilon_helper<long double> : _epsilon_helper_base<long double, 80'000> //why has this value got to be so large?
        {};
    } // namespace details

    template <typename _float>
    [[nodiscard]] constexpr bool equivalent(_float a, _float b) noexcept
    {
        static_assert(std::is_floating_point_v<_float>, "Raychel::equivalent<T> requires T to be a floating-point type!");
        constexpr _float epsilon = details::epsilon_helper<_float>::value;

        //handle signed zeroes and obviously correct cases such as infinity == infinity
        if (a == b)
            return true;

        //use a constant margin for small numbers
        if (std::abs(a - b) < epsilon)
            return true;

        //Use a relative margin for larger numbers and NaNs
        const auto diff = std::abs(a - b);
        const auto largest = std::max(std::abs(a), std::abs(b));

        return diff / largest <= epsilon;
    }

} // namespace Raychel

#endif //!RAYCHEL_EQUIVALENT_H