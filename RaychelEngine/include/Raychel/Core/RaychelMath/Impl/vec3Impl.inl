/**
*\file vec3Impl.inl
*\author weckyy702 (weckyy702@gmail.com)
*\brief Implementation for 3D vectors
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
#ifndef RAYCHEL_VEC3_IMP
#define RAYCHEL_VEC3_IMP

#include "../color.h"
#include "../vec2.h"
#include "../vec3.h"

namespace Raychel {

    template <typename T>
    constexpr vec3Imp<T>::vec3Imp(const vec2& v) noexcept : x(v.x), y(v.y), z(0)
    {}

    template <typename T>
    constexpr vec3Imp<T>::vec3Imp(const color& c) noexcept : x(c.r), y(c.g), z(c.b)
    {}

    template <typename T>
    template <typename To>
    constexpr vec3Imp<To> vec3Imp<T>::to() const noexcept
    {
        using vt = typename vec3Imp<To>::value_type;
        static_assert(std::is_convertible_v<value_type, vt>, "Vec3Imp<T>::to<To> requires T to be convertible to To!");

        return {static_cast<vt>(x), static_cast<vt>(y), static_cast<vt>(z)};
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator=(const vec2& v) noexcept
    {
        x = v.x;
        y = v.y;
        z = 0;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator=(const color& c) noexcept
    {
        x = c.r;
        y = c.g;
        z = c.b;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator+=(const vec3Imp& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator-=(const vec3Imp& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator*=(value_type s) noexcept
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator*=(const vec3Imp& v) noexcept
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator/=(value_type s) noexcept
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator/=(const vec3Imp& v) noexcept
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    template <typename T>
    constexpr vec3Imp<T>& vec3Imp<T>::operator%=(const vec3Imp& v) noexcept
    {
        if constexpr (std::is_integral_v<T>) {
            x %= v.x;
            y %= v.y;
            z %= v.z;
        } else {
            using std::fmod;
            x = T(fmod(x, v.x));
            y = T(fmod(y, v.y));
            z = T(fmod(z, v.z));
        }
        return *this;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vec3Imp<T>& v)
    {
        return os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    }

    template <typename T>
    constexpr vec3Imp<T> operator-(const vec3Imp<T>& v) noexcept
    {
        return {-v.x, -v.y, -v.z};
    }

    template <typename T>
    constexpr vec3Imp<T> operator+(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    template <typename T>
    constexpr vec3Imp<T> operator-(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    template <typename T>
    constexpr vec3Imp<T> operator*(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    template <typename T>
    constexpr vec3Imp<T> operator*(const vec3Imp<T>& v, T s) noexcept
    {
        return {v.x * s, v.y * s, v.z * s};
    }

    template <typename T>
    constexpr vec3Imp<T> operator/(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x / b.x, a.y / b.y, a.z / b.z};
    }

    template <typename T>
    constexpr vec3Imp<T> operator/(const vec3Imp<T>& v, T s) noexcept
    {
        return {T(v.x / s), T(v.y / s), T(v.z / s)};
    }

    template <typename T>
    vec3Imp<T> operator%(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        if constexpr (std::is_integral_v<T>) {
            return vec3Imp<T>(a.x % b.x, a.y % b.y, a.z % b.z);
        } else {
            using std::fmod;
            return vec3Imp<T>(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z));
        }
    }

    template <typename T>
    vec3Imp<T> operator%(const vec3Imp<T>& v, T m) noexcept
    {
        if constexpr (std::is_integral_v<T>) {
            return vec3Imp<T>(v.x % m, v.y % m, v.z % m);
        } else {
            using std::fmod;
            return vec3Imp<T>(fmod(v.x, m), fmod(v.y, m), fmod(v.z, m));
        }
    }

    template <typename T>
    constexpr bool operator==(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
#ifdef RAYCHEL_LOGICALLY_EQUAL
        return equivalent(a.x, b.x) && equivalent(a.y, b.y) && equivalent(a.z, b.z);
#else
        return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
#endif
    }

    template <typename T>
    constexpr vec3Imp<bool> operator<(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x < b.x, a.y < b.y, a.z < b.z};
    }

    template <typename T>
    constexpr vec3Imp<bool> operator<=(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x <= b.x, a.y <= b.y, a.z <= b.z};
    }

    template <typename T>
    constexpr vec3Imp<bool> operator>(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x > b.x, a.y > b.y, a.z > b.z};
    }

    template <typename T>
    constexpr vec3Imp<bool> operator>=(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {a.x >= b.x, a.y >= b.y, a.z >= b.z};
    }

    template <typename T>
    constexpr T dot(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    template <typename T>
    T mag(const vec3Imp<T>& v) noexcept
    {
        return T(std::sqrt(magSq(v)));
    }

    template <typename T>
    constexpr T magSq(const vec3Imp<T>& v) noexcept
    {
        return sq(v.x) + sq(v.y) + sq(v.z);
    }

    template <typename T>
    T dist(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return mag(a - b);
    }

    template <typename T>
    constexpr T distSq(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return magSq(a - b);
    }

    template <typename T>
    vec3Imp<T> max(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        using std::max;
        return {max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)};
    }

    template <typename T>
    vec3Imp<T> min(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        using std::min;
        return {min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
    }

    template <typename T, typename>
    vec3Imp<T> normalize(const vec3Imp<T>& v) noexcept
    {
        return v / mag(v);
    }

    template <typename T, typename>
    vec3Imp<T> abs(const vec3Imp<T>& v) noexcept
    {
        using std::abs;
        return {abs(v.x), abs(v.y), abs(v.z)};
    }

    template <typename T, typename>
    vec3Imp<T> sin(const vec3Imp<T>& v) noexcept
    {
        using std::sin;
        return {sin(v.x), sin(v.y), sin(v.z)};
    }

    template <typename T, typename>
    vec3Imp<T> cos(const vec3Imp<T>& v) noexcept
    {
        using std::cos;
        return {cos(v.x), cos(v.y), cos(v.z)};
    }

    // clang-format off

    template <typename T, typename>
    constexpr vec3Imp<T> cross(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return {
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        };
    }

    template <typename T, typename>
    vec3Imp<T> rotateX(const vec3Imp<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return {
            v.x,
            v.y * cos(theta) - v.z * sin(theta),
            v.y * sin(theta) + v.z * cos(theta)
        };
    }

    template <typename T, typename>
    vec3Imp<T> rotateY(const vec3Imp<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return {
            v.x * cos(theta) + v.z * sin(theta),
            v.y,
            -v.x * sin(theta) + v.z * cos(theta)
        };
    }

    template <typename T, typename>
    vec3Imp<T> rotateZ(const vec3Imp<T>& v, T theta) noexcept
    {
        //Raychels z-axis still seems to be inverted, so we have to invert some of the components
        using std::sin, std::cos;
        return {
            v.x * cos(theta) - v.y * sin(theta),
            v.x * sin(theta) + v.y * cos(theta),
            v.z
        };
    }

    // clang-format on

    template <typename T>
    constexpr vec3Imp<T> lerp(const vec3Imp<T>& a, const vec3Imp<T>& b, T x) noexcept
    {
        return (x * b) + ((1.0 - x) * a);
    }

    template <typename T, typename>
    constexpr vec3Imp<T> reflect(const vec3Imp<T>& direction, const vec3Imp<T>& normal) noexcept
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);
        return direction - (normal * T(dot(direction, normal) * 2.0));
    }

} // namespace Raychel

#endif /*!RAYCHEL_VEC3_IMP*/
