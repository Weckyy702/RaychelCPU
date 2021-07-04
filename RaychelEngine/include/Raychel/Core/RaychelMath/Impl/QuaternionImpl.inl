/**
*\file QuaternionImpl.inl
*\author weckyy702 (weckyy702@gmail.com)
*\brief Implementation for quaternions
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
#ifndef RAYCHEL_QUATERNION_IMP
#define RAYCHEL_QUATERNION_IMP

#include <type_traits>
#include "../Quaternion.h"
#include "../vec3.h"
#include "Raychel/Core/RaychelMath/math.h"

namespace Raychel {

    template <typename T>
    QuaternionImp<T>::QuaternionImp(const vec3& _axis, value_type theta)
    {
        const auto half_theta = theta / 2;

        r = std::cos(half_theta);

        const auto s = std::sin(half_theta);
        const auto axis = normalize(_axis);

        i = axis.x * s;
        j = axis.y * s;
        k = axis.z * s;
    }

    template <typename T>
    template <typename To>
    constexpr QuaternionImp<To> QuaternionImp<T>::to() const noexcept
    {
        static_assert(std::is_convertible_v<T, To>, "Raychel::QuaternionImp<T>::to<To> requires T to be convetibel to To!");

        return {static_cast<To>(r), static_cast<To>(i), static_cast<To>(j), static_cast<To>(k)};
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator+=(const QuaternionImp& q)
    {
        r += q.r;
        i += q.i;
        j += q.j;
        k += q.k;

        return *this;
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator-=(const QuaternionImp& q)
    {
        r -= q.r;
        i -= q.i;
        j -= q.j;
        k -= q.k;

        return *this;
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator*=(value_type s)
    {
        r *= s;
        i *= s;
        j *= s;
        k *= s;

        return *this;
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator*=(const QuaternionImp<T>& q)
    {
        value_type _r = r;
        value_type _i = i;
        value_type _j = j;
        value_type _k = k;

        r = _r * q.r - _i * q.i - _j * q.j - _k * q.k;
        i = _r * q.i + _i * q.r + _j * q.k - _k * q.j;
        j = _r * q.j - _i * q.k + _j * q.r + _k * q.i;
        k = _r * q.k + _i * q.j - _j * q.i + _k * q.r;

        return *this;
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator/=(value_type s)
    {
        r /= s;
        i /= s;
        j /= s;
        k /= s;

        return *this;
    }

    template <typename T>
    constexpr QuaternionImp<T>& QuaternionImp<T>::operator/=(const QuaternionImp& q)
    {
        return (*this) *= inverse(q);
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const QuaternionImp<T>& obj)
    {
        return os << "{ " << obj.r << ", " << obj.i << ", " << obj.j << ", " << obj.k << " }";
    }

    template <typename T>
    constexpr QuaternionImp<T> operator-(const QuaternionImp<T>& q)
    {
        return {-q.r, -q.i, -q.j, -q.k};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator+(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        return {a.r + b.r, a.i + b.i, a.j + b.j, a.k + b.k};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator-(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        return {a.r - b.r, a.i - b.i, a.j - b.j, a.k - b.k};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator*(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        const auto r = a.r * b.r - a.i * b.i - a.j * b.j - a.k * b.k;
        const auto i = a.r * b.i + a.i * b.r + a.j * b.k - a.k * b.j;
        const auto j = a.r * b.j - a.i * b.k + a.j * b.r + a.k * b.i;
        const auto k = a.r * b.k + a.i * b.j - a.j * b.i + a.k * b.r;

        return {r, i, j, k};
    }

    template <typename T>
    vec3Imp<T> operator*(const vec3Imp<T>& v, const QuaternionImp<T>& _q)
    {
        const auto q = normalize(_q);

        //following is the expanded and somewhat optimized version of q * p * q^-1 with p = QuaternionImp{0.0, v.x, v.y, v.z}
        const auto r = q.i * v.x + q.j * v.y + q.k * v.z;
        const auto i = q.r * v.x + q.j * v.z - q.k * v.y;
        const auto j = q.r * v.y - q.i * v.z + q.k * v.x;
        const auto k = q.r * v.z + q.i * v.y - q.j * v.x;

        const auto x = r * q.i + i * q.r - j * q.k + k * q.j;
        const auto y = r * q.j + i * q.k + j * q.r - k * q.i;
        const auto z = r * q.k - i * q.j + j * q.i + k * q.r;

        return vec3Imp<T>{x, y, z};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator*(const QuaternionImp<T>& q, T s)
    {
        return {q.r * s, q.i * s, q.j * s, q.k * s};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator/(const QuaternionImp<T>& q, T s)
    {
        return {q.r / s, q.i / s, q.j / s, q.k / s};
    }

    template <typename T>
    constexpr QuaternionImp<T> operator/(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        return a * inverse(b);
    }

    template <typename T>
    constexpr bool operator==(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
#ifdef RAYCHEL_LOGICALLY_EQUAL
        return equivalent(a.r, b.r) && equivalent(a.i, b.i) && equivalent(a.j, b.j) && equivalent(a.k, b.k);
#else
        return (a.r == b.r) && (a.i == b.i) && (a.j == b.j) && (a.k == b.k);
#endif
    }

    template <typename T>
    constexpr T dot(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        return a.r * b.r + a.i * b.i + a.j * b.j + a.k * b.k;
    }

    template <typename T>
    T mag(const QuaternionImp<T>& q)
    {
        return std::sqrt(sq(q.r) + sq(q.i) + sq(q.j) + sq(q.k));
    }

    template <typename T>
    constexpr T magSq(const QuaternionImp<T>& q)
    {
        return sq(q.r) + sq(q.i) + sq(q.j) + sq(q.k);
    }

    template <typename T, typename>
    QuaternionImp<T> normalize(const QuaternionImp<T>& q)
    {
        return q / mag(q);
    }

    template <typename T>
    constexpr QuaternionImp<T> conjugate(const QuaternionImp<T>& q)
    {
        return {q.r, -q.i, -q.j, -q.k};
    }

    template <typename T>
    constexpr QuaternionImp<T> inverse(const QuaternionImp<T>& q)
    {
        return conjugate(q) / magSq(q);
    }

    template <typename T>
    QuaternionImp<T> lerp(const QuaternionImp<T>& _a, const QuaternionImp<T>& _b, T x) noexcept
    {
        constexpr auto threshold = 0.995;

        const auto a = normalize(_a);
        const auto b = normalize(_b);

        auto d = dot(a.v(), b.v());

        if (d < 0.0) {
            a *= -1;
            b *= -1;
        }

        //if the Quaternions are very similar, just lerp them
        if (d >= threshold) {
            return normalize(a * x + b * (1.0 - x));
        }

        const auto theta0 = std::acos(d);
        const auto theta = theta0 * x;
        const auto sinTheta = std::sin(theta);
        const auto sinTheta0 = std::sin(theta0);

        const auto s1 = sinTheta / sinTheta0;
        const auto s0 = std::cos(theta) - (d * s1);

        return (a * s0) + (b * s1);
    }

    template <typename T>
    vec3Imp<T> orthogonal(const vec3Imp<T>& v)
    {
        auto orth = cross(vec3Imp<T>{1, 0, 0}, v);
        if(magSq(orth) == 0) {
            orth = cross(vec3Imp<T>{0, 1, 0}, v);
        }
        return normalize(orth);
    }

    template <typename T>
    QuaternionImp<T> look_at(const vec3Imp<T>& old_forward, const vec3Imp<T>& new_forward) noexcept
    {
        constexpr auto threshold = (T)0.9995;

        const auto k_cos_theta = dot(old_forward, new_forward);
        const auto k = std::sqrt(magSq(old_forward) * magSq(new_forward));

        if ((k_cos_theta / k) < -threshold) {
            const auto orth = orthogonal(old_forward);
            return QuaternionImp<T>{
                0,
                orth.x,
                orth.y,
                orth.z
            };
        }

        const auto ijk = cross(old_forward, new_forward);

        return normalize(QuaternionImp<T>{
            k_cos_theta + k,
            ijk.x,
            ijk.y,
            ijk.z
        });
    }
} // namespace Raychel

#endif // RAYCHEL_QUATERNION_IMP