#ifndef RAYCHEL_COLOR_IMP
#define RAYCHEL_COLOR_IMP
#pragma once

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
	colorImp<bool> operator==(const colorImp<T>& a, const colorImp<T>& b)
	{
		return { a.r == b.r, a.g == b.g, a.b == b.b};
	}

	template<typename T>
	colorImp<bool> operator!=(const colorImp<T>& a , const colorImp<T>& b)
	{
		return { a.r != b.r, a.g != b.g, a.b != b.b };
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
}

#endif /*RAYCHEL_COLOR_IMP*/
