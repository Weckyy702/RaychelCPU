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
#pragma once

#include <limits>

#include "../color.h"
#include "../vec2.h"
#include "../vec3.h"

namespace Raychel {

	template<typename T>
	inline colorImp<T> _ensureValid(const colorImp<T>& c) {
		using std::max;
		return { max<T>(c.r, 0), max<T>(c.g, 0), max<T>(c.b, 0) };
	}

	template<typename T>
	colorImp<T>::operator const value_type* () const
	{
		return &r;
	}

	template<typename T>
	colorImp<T>::colorImp(const vec3& v)
	{
		using std::abs;
		r = abs(v.x);
		g = abs(v.y);
		b = abs(v.z);
	}

	template<typename T>
	colorImp<T>::colorImp(const vec2& v)
	{
		using std::abs;
		r = abs(v.x);
		g = abs(v.y);
		b = 0;
	}

	template<typename T>
	template<typename To>
	colorImp<To> colorImp<T>::to() const noexcept
	{
		using vt = typename colorImp<To>::value_type;
		static_assert(std::is_convertible_v<value_type, To>, "ColorImp<T>::to<To> requires T to be convertible to To!");
		
		constexpr vt max = std::numeric_limits<vt>::max()-1;

		if constexpr (std::is_integral_v<vt> && std::is_floating_point_v<value_type>) {

			//if the internal representatino is in 0...1 range, convert to 0...max
			return _ensureValid<vt>({ static_cast<vt>(r*max), static_cast<vt>(g*max), static_cast<vt>(b*max) });
		} else {
			
			return _ensureValid<vt>({ static_cast<vt>(r), static_cast<vt>(g), static_cast<vt>(b) });
		}
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator=(const vec3& v)
	{
		r = abs(v.x);
		g = abs(v.y);
		b = abs(v.z);
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator=(const vec2& v)
	{
		r = abs(v.x);
		g = abs(v.y);
		b = 0;
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator+=(const colorImp& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator-=(const colorImp& c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator*=(value_type s)
	{
		r *= s;
		g *= s;
		b *= s;
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator*=(const colorImp& c)
	{
		r *= c.r;
		g *= c.g;
		b *= c.b;
		return *this;
	}

	template<typename T>
	colorImp<T>& colorImp<T>::operator/=(value_type s)
	{
		r /= s;
		g /= s;
		b /= s;
		return *this;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const colorImp<T>& c)
	{
		return os << "{ " << c.r << ", " << c.g << ", " << c.b << " }";
	}

	template<typename T>
	colorImp<T> operator-(const colorImp<T>& c)
	{
		return _ensureValid({ 1.0 - c.r, 1.0 - c.g, 1.0 - c.b});
	}

	template<typename T>
	colorImp<T> operator+(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r + b.r, a.g + b.g, a.b + b.b };
	}

	template<typename T>
	colorImp<T> operator-(const colorImp<T>& a, const colorImp<T>& b)
	{
		return _ensureValid({ a.r + b.r, a.g + b.g, a.b + b.b });
	}

	template<typename T>
	colorImp<T> operator*(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r * b.r, a.g * b.g, a.b * b.b };
	}

	template<typename T>
	colorImp<T> operator*(const colorImp<T>& c, T s)
	{
		return  { c.r * s, c.g * s, c.b * s };
	}

	template<typename T>
	colorImp<T> operator/(const colorImp<T>& c, T s)
	{
		return { c.r / s, c.g / s, c.b / s };
	}

	template<typename T>
	bool operator==(const colorImp<T>& a, const colorImp<T>& b)
	{
		return ( a.r == b.r ) && ( a.g == b.g ) && ( a.b == b.b );
	}

	template<typename T>
	colorImp<bool> operator<(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r < b.r, a.g < b.g, a.b < b.b };
	}

	template<typename T>
	colorImp<bool> operator<=(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r <= b.r, a.g <= b.g, a.b <= b.b };
	}

	template<typename T>
	colorImp<bool> operator>(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r > b.r, a.g > b.g, a.b > b.b };
	}

	template<typename T>
	colorImp<bool> operator>=(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r >= b.r, a.g >= b.g, a.b >= b.b };
	}

	template<typename T>
	colorImp<T> abs(const colorImp<T>& c)
	{
		using std::abs;
		return { abs(c.r), abs(c.g), abs(c.b) };
	}

	template<typename T>
	colorImp<T> max(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { max(a.r, b.r), max(a.g, b.g), max(a.b, b.b) };
	}

	template<typename T>
	colorImp<T> min(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { min(a.r, b.r), min(a.g, b.g), min(a.b, b.b) };
	}

	template<typename T>
	T brightness(const colorImp<T>& _c) {
		auto c = _ensureValid(_c);
		return (c.r + c.g + c.b) / T(3.0);
	}
}

#endif /*RAYCHEL_COLOR_IMP*/
