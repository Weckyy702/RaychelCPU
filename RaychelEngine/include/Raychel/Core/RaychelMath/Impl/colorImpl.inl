/**
*\file colorImpl.inl
*\author weckyy702 (weckyy702@gmail.com)
*\brief Implementation for RGB colors
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
#ifndef RAYCHEL_COLOR_IMP
#define RAYCHEL_COLOR_IMP

#include <limits>

#include "../color.h"
#include "../vec2.h"
#include "../vec3.h"

namespace Raychel {

    namespace details {

        template <typename T>
        constexpr colorImp<T> ensureValidColor(const colorImp<T>& c) noexcept
        {
            using std::clamp, std::max;
            using vt = typename colorImp<T>::value_type;

            if constexpr (std::is_floating_point_v<vt>) {
                return {
                    clamp<vt>(c.r, 0, 1.0), clamp<vt>(c.g, 0, 1.0),
                    clamp<vt>(c.b, 0, 1.0)};
            }

            //all integral types wrap around on overflow, so we don't need to clamp off anything larger than std::numeric_limits<T>::max()
            return {
                max<vt>(c.r, 0), max<vt>(c.g, 0),
                max<vt>(c.b, 0)};
        }

        template<typename T, typename To>
        constexpr colorImp<To> convert_float(const colorImp<T>& _c) noexcept
        {
            const auto c = ensureValidColor(_c);
            if constexpr(std::is_integral_v<To>) {
                constexpr auto max = std::numeric_limits<To>::max();

                return colorImp<To>(c.r * max, c.g * max, c.b * max);
            } 
            return colorImp<To>(c.r, c.g, c.b);
        }
    
        template<typename T, typename To>
        constexpr colorImp<To> convert_integral(const colorImp<T>& _c) noexcept
        {
            const auto c = ensureValidColor(_c);

            if constexpr(std::is_floating_point_v<To>) {
                constexpr To max = std::numeric_limits<T>::max();

                return colorImp<To>(
                    c.r / max,
                    c.g / max,
                    c.b / max
                );
            }
            return colorImp<To>(c.r, c.g, c.b);
        }
    }

    template <typename T>
    constexpr colorImp<T>::operator const value_type*() const noexcept
    {
        return &r;
    }

    template <typename T>
    constexpr colorImp<T>::colorImp(const vec3& v) noexcept
    {
        using std::abs;
        r = abs(v.x);
        g = abs(v.y);
        b = abs(v.z);
    }

    template <typename T>
    constexpr colorImp<T>::colorImp(const vec2& v) noexcept
    {
        using std::abs;
        r = abs(v.x);
        g = abs(v.y);
        b = 0;
    }

    template <typename T>
    template <typename To>
    constexpr colorImp<To> colorImp<T>::to() const noexcept
    {
        using vt = typename colorImp<To>::value_type;
        static_assert(
            std::is_convertible_v<value_type, To>,
            "ColorImp<T>::to<To> requires T to be convertible to To!");

        if constexpr(std::is_floating_point_v<value_type>) {
            return details::convert_float<value_type, vt>(*this);
        } else {
            return details::convert_integral<value_type, vt>(*this);
        }
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator=(const vec3& v) noexcept
    {
        r = abs(v.x);
        g = abs(v.y);
        b = abs(v.z);

        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator=(const vec2& v) noexcept
    {
        r = abs(v.x);
        g = abs(v.y);
        b = 0;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator+=(const colorImp& c) noexcept
    {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator-=(const colorImp& c) noexcept
    {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator*=(value_type s) noexcept
    {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator/=(const colorImp& c) noexcept
    {
        r /= c.r;
        g /= c.g;
        b /= c.b;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator*=(const colorImp& c) noexcept
    {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        return *this;
    }

    template <typename T>
    constexpr colorImp<T>& colorImp<T>::operator/=(value_type s) noexcept
    {
        r /= s;
        g /= s;
        b /= s;
        return *this;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const colorImp<T>& c)
    {
        return os << "{ " << c.r << ", " << c.g << ", " << c.b << " }";
    }

    template <typename T>
    constexpr colorImp<T> operator-(const colorImp<T>& c) noexcept
    {
        using value_type = typename colorImp<T>::value_type;

        if constexpr (std::is_floating_point_v<value_type>)
            return details::ensureValidColor({1.0 - c.r, 1.0 - c.g, 1.0 - c.b});
        else {
            constexpr auto max = std::numeric_limits<value_type>::max();
            return details::ensureValidColor({max - c.r, max - c.g, max - c.b});
        }
    }

    template <typename T>
    constexpr colorImp<T>
    operator+(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r + b.r, a.g + b.g, a.b + b.b);
    }

    template <typename T>
    constexpr colorImp<T>
    operator-(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r - b.r, a.g - b.g, a.b - b.b);
    }

    template <typename T>
    constexpr colorImp<T>
    operator*(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r * b.r, a.g * b.g, a.b * b.b);
    }

    template <typename T>
    constexpr colorImp<T> operator*(const colorImp<T>& c, T s) noexcept
    {
        return colorImp<T>(c.r * s, c.g * s, c.b * s);
    }

    template <typename T>
    constexpr colorImp<T>
    operator/(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r / b.r, a.g / b.g, a.b / b.b);
    }

    template <typename T>
    constexpr colorImp<T> operator/(const colorImp<T>& c, T s) noexcept
    {
        return colorImp<T>(c.r / s, c.g / s, c.b / s);
    }

    template <typename T>
    constexpr bool
    operator==(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
#ifdef RAYCHEL_LOGICALLY_EQUAL
        return equivalent(a.r, b.r) && equivalent(a.g, b.g) &&
               equivalent(a.b, b.b);
#else
        return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
#endif
    }

    template <typename T>
    constexpr colorImp<bool>
    operator<(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r < b.r, a.g < b.g, a.b < b.b};
    }

    template <typename T>
    constexpr colorImp<bool>
    operator<=(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r <= b.r, a.g <= b.g, a.b <= b.b};
    }

    template <typename T>
    constexpr colorImp<bool>
    operator>(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r > b.r, a.g > b.g, a.b > b.b};
    }

    template <typename T>
    constexpr colorImp<bool>
    operator>=(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r >= b.r, a.g >= b.g, a.b >= b.b};
    }

    template <typename T>
    constexpr colorImp<T>
    max(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        using std::max;
        return colorImp<T>(max(a.r, b.r), max(a.g, b.g), max(a.b, b.b));
    }

    template <typename T>
    constexpr colorImp<T>
    min(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        using std::min;
        return colorImp<T>(min(a.r, b.r), min(a.g, b.g), min(a.b, b.b));
    }

    template <typename T>
    constexpr T brightness(const colorImp<T>& c) noexcept
    {
        return (c.r + c.g + c.b) / 3.0;
    }
} // namespace Raychel

#endif /*RAYCHEL_COLOR_IMP*/
