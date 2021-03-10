#ifndef RAYCHEL_VEC2_IMP
#define RAYCHEL_VEC2_IMP
#pragma once

#include "../../utils.h"
#include "../vec2.h"
#include "../vec3.h"
#include "../color.h"

namespace Raychel {
	template<typename T>
	vec2Imp<T>::vec2Imp(const vec3& v)
		:x(v.x), y(v.y)
	{}

	template<typename T>
	vec2Imp<T>::vec2Imp(const color& c)
		: x(c.r), y(c.g)
	{}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator=(const vec3& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator=(const color& c)
	{
		x = c.r;
		y = c.g;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator+=(const vec2Imp& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator-=(const vec2Imp& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator*=(value_type s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator*=(const vec2Imp& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator/=(value_type s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator/=(const vec2Imp& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	template<typename T>
	vec2Imp<T>& vec2Imp<T>::operator%=(const vec2Imp& v)
	{
		if constexpr (std::is_integral_v<T>) {
			x %= v.x;
			y %= v.y;
		}
		else {
			using std::modf;
			x = T(fmodl(x, v.x));
			y = T(fmodl(y, v.y));
		}
		return *this;
	}

	template<typename T>
	vec2Imp<T> operator-(const vec2Imp<T>& v)
	{
		return { -v.x, -v.y };
	}

	template<typename T>
	vec2Imp<T> operator+(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x + b.x, a.y + b.y };
	}

	template<typename T>
	vec2Imp<T> operator-(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x - b.x, a.y - b.y };
	}

	template<typename T>
	vec2Imp<T> operator*(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x * b.x, a.y * b.y };
	}

	template<typename T>
	vec2Imp<T> operator*(const vec2Imp<T>& v, T s)
	{
		return { v.x * s, v.y * s };
	}

	template<typename T>
	vec2Imp<T> operator/(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x / b.x, a.y / b.y };
	}

	template<typename T>
	vec2Imp<T> operator/(const vec2Imp<T>& v, T s)
	{
		return { T(v.x / s), T(v.y / s) };
	}

	template<typename T>
	vec2Imp<T> operator%(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		if constexpr (std::is_integral_v<T>) {
			return { a.x % b.x, a.y % b.y };
		}
		else {
			using std::modf;
			return { modf(a.x, b.x), modf(a.y, b.y) };
		}
	}

	template<typename T>
	bool operator==(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return (a.x == b.x) && (a.y == b.y);
	}

	template<typename T>
	vec2Imp<bool> operator==(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x == b.x, a.y == b.y };
	}

	template<typename T>
	vec2Imp<bool> operator!=(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x != b.x, a.y != b.y };
	}

	template<typename T>
	vec2Imp<bool> operator<(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x < b.x, a.y < b.y };
	}

	template<typename T>
	vec2Imp<bool> operator<=(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x <= b.x, a.y <= b.y };
	}

	template<typename T>
	vec2Imp<bool> operator>(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x > b.x, a.y > b.y };
	}

	template<typename T>
	vec2Imp<bool> operator>=(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return { a.x >= b.x, a.y >= b.y };
	}

	template<typename T>
	T dot(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return(a.x * b.x) + (a.y * b.y);
	}

	template<typename T>
	T mag(const vec2Imp<T>& v)
	{
		return T(std::sqrt(magSq(v)));
	}

	template<typename T>
	T magSq(const vec2Imp<T>& v)
	{
		return sq(v.x) + sq(v.y);
	}

	template<typename T>
	vec2Imp<T> normalize(const vec2Imp<T>& v)
	{
		return v * inv_sqrt(magSq(v));
	}

	template<typename T>
	vec2Imp<T> abs(const vec2Imp<T>& v)
	{
		using std::abs;
		return { abs(v.x), abs(v.y) };
	}

	template<typename T>
	vec2Imp<T> max(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		using std::max;
		return { max(a.x, b.x), max(a.y, b.y) };
	}

	template<typename T>
	vec2Imp<T> min(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		using std::min;
		return { min(a.x, b.x), min(a.y, b.y) };
	}

	template<typename T>
	vec2Imp<T> sin(const vec2Imp<T>& v)
	{
		using std::sin;
		return { sin(v.x), sin(v.y) };
	}

	template<typename T>
	vec2Imp<T> cos(const vec2Imp<T>& v)
	{
		using std::cos;
		return { cos(v.x), cos(v.y) };
	}

	template<typename T>
	vec2Imp<T> pow(const vec2Imp<T>& v, T p)
	{
		using std::pow;
		return { pow(v.x, p), pow(v.y, p) };
	}

	template<typename T>
	vec2Imp<T> pow(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		using std::pow;
		return { pow(a.x, b.x), pow(a.y, b.y) };
	}

	template<typename T>
	T dist(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return mag(a - b);
	}

	template<typename T>
	T distSq(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return magSq(a - b);
	}

	template<typename T>
	vec2Imp<T> rotate(const vec2Imp<T>& v, T theta)
	{
		using std::sin, std::cos;
		return {
			v.x * cos(theta) - v.y * sin(theta),
			v.x * sin(theta) + v.y * cos(theta)
		};
	}
}


#endif // !RAYCHEL_VEC2_IMP
