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

#include "../utils.h"

namespace Raychel {

	/**
	*\brief Quaternion quantity
	*
	*\tparam _number Type of the Quaternion. Must be arithmetic
	*/
	template<typename _number>
	class QuaternionImp {
	public:
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:
		static_assert(std::is_arithmetic_v<value_type>, "Raychel::Quaternion<T> requires T to be of arithmetic type!");
		using vec3 = vec3Imp<value_type>;

	public:

		/**
		*\brief Construct a new QuaternionImp object. Will rotate 0° around positive y
		*
		*/
		QuaternionImp()
			:QuaternionImp(vec3{0, 1, 0}, 0)
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
		QuaternionImp(value_type _r, value_type _i, value_type _j, value_type _k)
            :r{_r}, i{_i}, j{_j}, k{_k}
        {}

        QuaternionImp(const vec3&, value_type);

		/**
		*\brief Return the vector part of the quaternion
		*
		*\return vec3 
		*/
        inline vec3 v() const noexcept
		{
            return {i, j, k};
        }

		/**
		*\brief Return the scalar part of the quaternion
		*
		*\return value_type 
		*/
        inline value_type s() const noexcept
		{
            return r;
        }

		/**
		*\brief Convert the quaternion to another quaternion of type To
		*
		*\tparam To Type of the converted quaternion
		*\return QuaternionImp<To> 
		*/
		template<typename To>
		QuaternionImp<To> to() const noexcept;

        QuaternionImp& operator+=(const QuaternionImp&);
        QuaternionImp& operator-=(const QuaternionImp&);
        QuaternionImp& operator*=(value_type);
        QuaternionImp& operator*=(const QuaternionImp&);
        QuaternionImp& operator/=(value_type);

        value_type r{0}, i{0}, j{0}, k{0};
	};

	template<typename T>
	std::ostream& operator<<(std::ostream&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator+(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator-(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator*(const QuaternionImp<T>&, const QuaternionImp<T>&);

	/**
	*\brief Rotate a vector using a quaternion
	*
	*\tparam T Type of the vector and quaternion
	*\return vec3Imp<T> the rotated vector
	*/
    template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator*(const QuaternionImp<T>&, T);

	template<typename T>
	inline QuaternionImp<T> operator*(T s, const QuaternionImp<T>& v)
	{
		return v * s;
	}

	template<typename T>
	QuaternionImp<T> operator/(const QuaternionImp<T>&, T);

	template<typename T>
	bool operator==(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	bool operator!=(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
		return !(a == b);
	}

	template<typename T>
	T dot(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	T mag(const QuaternionImp<T>&);

	template<typename T>
	T magSq(const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> normalize(const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> conjugate(const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> inverse(const QuaternionImp<T>&);

		/**
	*\brief Linearly interpolate two Quaternions
	*
	*\tparam T Type of the quaternion
	*\param _a first quaternion (x=0.0)
	*\param _b second quaternion (x=1.0)
	*\param x value of interpolation
	*\return QuaternionImp<T> 
	*/
	template<typename T>
	QuaternionImp<T> lerp(const QuaternionImp<T>& _a, const QuaternionImp<T>& _b, float x)
	{
		constexpr auto threshold = 0.995;

		auto a = normalize(_a);
		auto b = normalize(_b);

		auto d = dot(a.v(), b.v());

		if(d < 0.0) {
			a *= -1;
			b *= -1;
		}

		//if the Quaternions are very similar, just lerp them
		if(d >= threshold) {
			return normalize(a * x + b * (1.0 - x));
		}

		auto theta0 = std::acos(d);
		auto theta = theta0 * x;
		auto sinTheta = std::sin(theta);
		auto sinTheta0 = std::sin(theta0);

		auto s1 = sinTheta / sinTheta0;
		auto s0 = std::cos(theta) - (d * s1);

		return (a * s0) + (b * s1);

	}

}

#endif /*!RAYCHEL_QUATERNION_H*/
