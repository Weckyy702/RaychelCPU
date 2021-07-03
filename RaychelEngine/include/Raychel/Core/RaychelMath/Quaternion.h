/**
*\file Quaternion.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Quatenions
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
#ifndef RAYCHEL_QUATERNION_H
#define RAYCHEL_QUATERNION_H

#include <type_traits>
#include "../utils.h"

namespace Raychel {

    /**
	*\brief Quaternion quantity
	*
	*\tparam _number Type of the Quaternion. Must be arithmetic
	*/
    template <typename _number>
    struct QuaternionImp
    {
    public:
        using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;
        static_assert(std::is_floating_point_v<value_type>, "Raychel::QuaternionImp<T> expects T to be of floating point type!");

    private:
        static_assert(std::is_arithmetic_v<value_type>, "Raychel::Quaternion<T> requires T to be of arithmetic type!");
        using vec3 = vec3Imp<value_type>;

    public:
        /**
		*\brief Construct a new QuaternionImp object. Will rotate 0° around positive y
		*
		*/
        constexpr QuaternionImp() : QuaternionImp{1, 0, 0, 0}
        {}

        /**
		*\brief Construct a new QuaternionImp object
		*
		*\param _r real component of the quaternion
		*\param _i imaginary component of the quaternion i
		*\param _j imaginary component of the quaternion j
		*\param _k imaginary component of the quaternion k
		*
		*\note Constructing quaternions from raw data is not recommended
		*/
        constexpr QuaternionImp(value_type _r, value_type _i, value_type _j, value_type _k) : r{_r}, i{_i}, j{_j}, k{_k}
        {}

        QuaternionImp(const vec3&, value_type);

        /**
		*\brief Return the vector part of the quaternion
		*
		*\return vec3 
		*/
        constexpr vec3 v() const noexcept
        {
            return {i, j, k};
        }

        /**
		*\brief Return the scalar part of the quaternion
		*
		*\return value_type 
		*/
        constexpr value_type s() const noexcept
        {
            return r;
        }

        /**
		*\brief Convert the quaternion to another quaternion of type To
		*
		*\tparam To Type of the converted quaternion
		*\return QuaternionImp<To> 
		*/
        template <typename To>
        constexpr QuaternionImp<To> to() const noexcept;

        constexpr QuaternionImp& operator+=(const QuaternionImp&);
        constexpr QuaternionImp& operator-=(const QuaternionImp&);
        constexpr QuaternionImp& operator*=(value_type);
        constexpr QuaternionImp& operator*=(const QuaternionImp&);
        constexpr QuaternionImp& operator/=(value_type);
        constexpr QuaternionImp& operator/=(const QuaternionImp&);

        value_type r{0}, i{0}, j{0}, k{0};
    };

    template <typename T>
    std::ostream& operator<<(std::ostream&, const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> operator-(const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> operator+(const QuaternionImp<T>&, const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> operator-(const QuaternionImp<T>&, const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> operator*(const QuaternionImp<T>&, const QuaternionImp<T>&);

    /**
	*\brief Rotate a vector using a quaternion
	*
	*\tparam T Type of the vector and quaternion
	*\return vec3Imp<T> the rotated vector
	*/
    template <typename T>
    vec3Imp<T> operator*(const vec3Imp<T>&, const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> operator*(const QuaternionImp<T>&, T);

    template <typename T>
    constexpr QuaternionImp<T> operator*(T s, const QuaternionImp<T>& v)
    {
        return v * s;
    }

    template <typename T>
    constexpr QuaternionImp<T> operator/(const QuaternionImp<T>&, T);

    template<typename T>
    constexpr QuaternionImp<T> operator/(const QuaternionImp<T>&, const QuaternionImp<T>&);

    template <typename T>
    constexpr bool operator==(const QuaternionImp<T>&, const QuaternionImp<T>&);

    template <typename T>
    constexpr bool operator!=(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
    {
        return !(a == b);
    }

    template <typename T>
    constexpr T dot(const QuaternionImp<T>&, const QuaternionImp<T>&);

    template <typename T>
    T mag(const QuaternionImp<T>&);

    template <typename T>
    constexpr T magSq(const QuaternionImp<T>&);

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    QuaternionImp<T> normalize(const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> conjugate(const QuaternionImp<T>&);

    template <typename T>
    constexpr QuaternionImp<T> inverse(const QuaternionImp<T>&);

    /**
	*\brief Smoothly interpolate two normalized Quaternions (Versors)
	*
	*\tparam T Type of the quaternion
	*\param _a first quaternion (x=0.0)
	*\param _b second quaternion (x=1.0)
	*\param x value of interpolation
	*\return QuaternionImp<T> the interpolated Quaternion
	*/
    template <typename T>
    QuaternionImp<T> lerp(const QuaternionImp<T>& _a, const QuaternionImp<T>& _b, T x) noexcept;

    /**
    *\brief Calculate the Quaternion to rotate old_forward onto new_forward
    *
    *\tparam T Type of the Quaternion
    *\param old_forward old forward vector
    *\param new_forward new forward vector
    *\return QuaternionImp<T> the Quaternion that rotates old onto new
    */
    template <typename T>
    QuaternionImp<T> look_at(const vec3Imp<T>& _old_forward, const vec3Imp<T>& _new_forward) noexcept;

} // namespace Raychel

#endif /*!RAYCHEL_QUATERNION_H*/
