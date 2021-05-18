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

#include "../utils.h"

namespace Raychel {

	/**
	*\brief RGB color value
	*
	*\tparam _number Type of color value. Must be arithmetic
	*/
	template<typename _number>
	struct colorImp {
	
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:
		
		static_assert(std::is_arithmetic_v<value_type>, "Raychel::color<T> requires T to be of arithmetic type!");
		
		using vec3 = vec3Imp<value_type>;
		using vec2 = vec2Imp<value_type>;

	public:

		constexpr colorImp() noexcept =default;

		constexpr explicit colorImp(value_type _b) noexcept
			:r(_b), g(_b), b(_b)
		{}

		constexpr colorImp(value_type _r, value_type _g) noexcept
			:r(_r), g(_g), b(0)
		{}

		constexpr colorImp(value_type _r, value_type _g, value_type _b) noexcept
			:r(_r), g(_g), b(_b)
		{}

		/**
		*\brief Convert the color to another color of type To
		*
		*\tparam To Type of the converted color
		*\return colorImp<_To> 
		*/
		template<typename To>
		constexpr colorImp<To> to() const noexcept;
		
		/**
		*\brief Convert the color to a pointer-to-red. For functions that need colors as arrays
		*
		*\return const value_type* the value array in RGB order
		*/
		constexpr explicit operator const value_type* () const noexcept;

		constexpr explicit colorImp(const vec3&) noexcept;
		constexpr explicit colorImp(const vec2&) noexcept;

		constexpr colorImp& operator=(const vec3&) noexcept;
		constexpr colorImp& operator=(const vec2&) noexcept;

		constexpr colorImp& operator+=(const colorImp&) noexcept;
		constexpr colorImp& operator-=(const colorImp&) noexcept;
		constexpr colorImp& operator*=(value_type) noexcept;
		constexpr colorImp& operator*=(const colorImp&) noexcept;
		constexpr colorImp& operator/=(value_type) noexcept;

		value_type r{0}, g{0}, b{0};
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const colorImp<T>& c);

	template<typename T>
	constexpr colorImp<T> operator-(const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> operator+(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> operator-(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> operator*(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> operator*(const colorImp<T>&, T) noexcept;

	template<typename T>
	constexpr colorImp<T> operator*(T s, const colorImp<T>& v) noexcept
	{
		return v * s;
	}

	template<typename T>
	constexpr colorImp<T> operator/(const colorImp<T>&, T) noexcept;

	template<typename T>
	constexpr bool operator==(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr bool operator!=(const colorImp<T>& a, const colorImp<T>& b) noexcept
	{
		return !(a == b);
	}

	template<typename T>
	constexpr colorImp<bool> operator<(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<bool> operator<=(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<bool> operator>(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<bool> operator>=(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> abs(const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> max(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr colorImp<T> min(const colorImp<T>&, const colorImp<T>&) noexcept;

	template<typename T>
	constexpr T brightness(const colorImp<T>&) noexcept;
}

#endif /*!RAYCHEL_COLOR_H*/
