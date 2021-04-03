/**
*\file color.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for RGB colors
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
#ifndef RAYCHEL_COLOR_H
#define RAYCHEL_COLOR_H
#pragma once

#include "../utils.h"

namespace Raychel {

	/**
	*\brief RGB color value
	*
	*\tparam _number Type of color value. Must be arithmetic
	*/
	template<RAYCHEL_NUMBER _number>
	struct colorImp {
	
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:
		
		RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::color<T> requires T to be of arithmetic type!");
		
		using vec3 = vec3Imp<value_type>;
		using vec2 = vec2Imp<value_type>;

	public:

		colorImp() = default;

		explicit colorImp(value_type _b)
			:r(_b), g(_b), b(_b)
		{}

		colorImp(value_type _r, value_type _g)
			:r(_r), g(_g), b(0)
		{}

		colorImp(value_type _r, value_type _g, value_type _b)
			:r(_r), g(_g), b(_b)
		{}

		/**
		*\brief Convert the color to another color of type _To
		*
		*\tparam _To Type of the converted color
		*\return colorImp<_To> 
		*/
		template<typename _To>
		colorImp<_To> to() const noexcept;
		
		/**
		*\brief Convert the color to a pointer-to-red. For functions that need colors as arrays
		*
		*\return const value_type* 
		*/
		explicit operator const value_type* () const;

		explicit colorImp(const vec3&);
		explicit colorImp(const vec2&);

		colorImp& operator=(const vec3&);
		colorImp& operator=(const vec2&);

		colorImp& operator+=(const colorImp&);
		colorImp& operator-=(const colorImp&);
		colorImp& operator*=(value_type);
		colorImp& operator*=(const colorImp&);
		colorImp& operator/=(value_type);

		value_type r= value_type(0), g= value_type(0), b= value_type(0);
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const colorImp<T>& c);

	template<typename T>
	colorImp<T> operator-(const colorImp<T>&);

	template<typename T>
	colorImp<T> operator+(const colorImp<T>&, const colorImp<T>);

	template<typename T>
	colorImp<T> operator-(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<T> operator*(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<T> operator*(const colorImp<T>&, T);

	template<typename T>
	inline colorImp<T> operator*(T s, const colorImp<T>& v)
	{
		return v * s;
	}

	template<typename T>
	colorImp<T> operator/(const colorImp<T>&, T);

	template<typename T>
	bool operator==(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	bool operator!=(const colorImp<T>& a, const colorImp<T>& b)
	{
		return !(a == b);
	}

	template<typename T>
	colorImp<bool> operator<(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<bool> operator<=(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<bool> operator>(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<bool> operator>=(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<T> abs(const colorImp<T>&);

	template<typename T>
	colorImp<T> max(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<T> min(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	inline colorImp<T> _ensureValid(const colorImp<T>& c);
}

#endif /*!RAYCHEL_COLOR_H*/
