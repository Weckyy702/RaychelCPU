/**
*\file vec3.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for 3 dimensional vector quantities
*\date 2021-03-24
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
#ifndef RAYCHEL_VEC3_H
#define RAYCHEL_VEC3_H
#pragma once

#include "../utils.h"

namespace Raychel {

	/**
	*\brief 3D vector
	*
	*\tparam _number Type of the vector. Must be arithmetic
	*/
	template<RAYCHEL_NUMBER _number>
	struct vec3Imp {

		//this ugly mess will have to stay until C++20
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:

		RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::vec3<T> requires T to be of arithmetic type!");
		using vec2 = vec2Imp<value_type>;
		using color = colorImp <value_type>;

	public:

		constexpr vec3Imp() = default;

		explicit constexpr vec3Imp(value_type _x)
			:x(_x)
		{}

		constexpr vec3Imp(value_type _x, value_type _y)
			: x(_x), y(_y)
		{}

		constexpr vec3Imp(value_type _x, value_type _y, value_type _z)
			: x(_x), y(_y), z(_z)
		{}

		/**
		*\brief Convert the vector to the same vector of another type
		*
		*\tparam To Type of the converted vector
		*\return vec3Imp<To> 
		*/
		template<typename To>
		vec3Imp<To> to() const noexcept;

		explicit vec3Imp(const vec2&);
		explicit vec3Imp(const color&);

		vec3Imp& operator=(const vec2&);
		vec3Imp& operator=(const color&);

		vec3Imp& operator+=(const vec3Imp&);
		vec3Imp& operator-=(const vec3Imp&);
		vec3Imp& operator*=(value_type);
		vec3Imp& operator*=(const vec3Imp&);
		vec3Imp& operator/=(value_type);
		vec3Imp& operator/=(const vec3Imp&);
		vec3Imp& operator%=(const vec3Imp&);

		value_type x= value_type(0), y= value_type(0), z= value_type(0);
	};

	template<typename T>
	std::ostream& operator<<(std::ostream&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> operator-(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> operator+(const vec3Imp<T>&, const vec3Imp<T>);

	template<typename T>
	vec3Imp<T> operator-(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>&, T);

	template<typename T>
	inline vec3Imp<T> operator*(T s, const vec3Imp<T>& v)
	{
		return v * s;
	}

	template<typename T>
	vec3Imp<T> operator/(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> operator/(const vec3Imp<T>&, T);

	template<typename T>
	vec3Imp<T> operator%(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	bool operator==(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	bool operator!=(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return !(a == b);
	}

	template<typename T>
	vec3Imp<bool> operator<(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<bool> operator<=(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<bool> operator>(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<bool> operator>=(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	T dot(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	T mag(const vec3Imp<T>&);

	template<typename T>
	T magSq(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> normalize(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> abs(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> max(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> min(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> sin(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> cos(const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> pow(const vec3Imp<T>&, T);

	template<typename T>
	vec3Imp<T> pow(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	T dist(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	T distSq(const vec3Imp<T>&, const vec3Imp<T>&);

	template<typename T>
	vec3Imp<T> cross(const vec3Imp<T>&, const vec3Imp<T>&);

	/**
	*\brief Rotate the vector theta radians around positive X
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
	template<typename T>
	vec3Imp<T> rotateX(const vec3Imp<T>& v, long double theta);

	/**
	*\brief Rotate the vector theta radians around positive Y
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
	template<typename T>
	vec3Imp<T> rotateY(const vec3Imp<T>& v, long double theta);

	/**
	*\brief Rotate the vector theta radians around positive Z
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
	template<typename T>
	vec3Imp<T> rotateZ(const vec3Imp<T>& v, long double theta);

	/**
	*\brief Linearly interpolate two vectors
	*
	*\tparam T Type of the vector
	*\param a first vector (x=0.0)
	*\param b second vector (x=1.0)
	*\param x value of interpolation
	*\return constexpr vec2Imp<T> 
	*/
	template<typename T>
	constexpr vec3Imp<T> lerp(const vec3Imp<T>& a, const vec3Imp<T>& b, long double x)
	{
		return (x * b) + ((1.0-x) * a);
	}
}

#endif /*!RAYCHEL_VEC3_H*/
