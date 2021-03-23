#ifndef RAYCHEL_VEC3_IMP
#define RAYCHEL_VEC3_IMP
#pragma once
#include "../vec3.h"
#include "../vec2.h"
#include "../color.h"

namespace Raychel {

	template<typename T>
	vec3Imp<T>::vec3Imp(const vec2& v)
		:x(v.x), y(v.y), z(0)
	{}

	template<typename T>
	vec3Imp<T>::vec3Imp(const color& c)
		: x(c.r), y(c.g), z(c.b)
	{}

	template<typename T>
	template<typename To>
	constexpr vec3Imp<To> vec3Imp<T>::to() const
	{
		using vt = typename colorImp<To>::value_type;
		static_assert(std::is_convertible_v<value_type, To>, "Vec3Imp<T>::to<To> requires T to be convertible to To!");

		return { static_cast<vt>(x), static_cast<vt>(y), static_cast<vt>(z) };
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator=(const vec2& v)
	{
		x = v.x;
		y = v.y;
		z = 0;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator=(const color& c)
	{
		x = c.r;
		y = c.g;
		z = c.b;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator+=(const vec3Imp& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator-=(const vec3Imp& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator*=(value_type s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator*=(const vec3Imp& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator/=(value_type s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator/=(const vec3Imp& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	template<typename T>
	vec3Imp<T>& vec3Imp<T>::operator%=(const vec3Imp& v)
	{
		if constexpr (std::is_integral_v<T>) {
			x %= v.x;
			y %= v.y;
			z %= v.z;
		} else {
			using std::modf;
			x = T(modf(x, v.x));
			y = T(modf(y, v.y));
			z = T(modf(z, v.z));
		}
		return *this;
	}

	template<typename T>
	std::ostream& operator<< (std::ostream& os, const vec3Imp<T>& v)
	{
		return os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
	}

	template<typename T>
	vec3Imp<T> operator-(const vec3Imp<T>& v)
	{
		return { -v.x, -v.y, -v.z };
	}

	template<typename T>
	vec3Imp<T> operator+(const vec3Imp<T>& a, const vec3Imp<T> b)
	{
		return { a.x + b.x, a.y + b.y, a.z + b.z };
	}

	template<typename T>
	vec3Imp<T> operator-(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return { a.x-b.x, a.y-b.y, a.z-b.z };
	}

	template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return {a.x * b.x, a.y * b.y, a.z * b.z};
	}

	template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>& v, T s)
	{
		return {v.x * s, v.y * s, v.z * s};
	}

	template<typename T>
	vec3Imp<T> operator/(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return {a.x / b.x, a.y / b.y, a.z / b.z};
	}

	template<typename T>
	vec3Imp<T> operator/(const vec3Imp<T>& v, T s)
	{
		return { T(v.x / s), T(v.y / s), T(v.z / s) };
	}

	template<typename T>
	vec3Imp<T> operator%(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		if constexpr (std::is_integral_v<T>) {
			return {a.x % b.x, a.y % b.y, a.z % b.z};
		}
		else {
			using std::modf;
			return { modf(a.x, b.x), modf(a.y, b.y), modf(a.z, b.z) };
		}
	}

	template<typename T>
	bool operator==(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
#ifdef RAYCHEL_LOGICALLY_EQUAL
		return equivalent(a.x, b.x) && equivalent(a.y, b.y) && equivalent(a.z, b.z);
#else
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
#endif
	}

	template<typename T>
	vec3Imp<bool> operator<(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return { a.x < b.x, a.y < b.y, a.z < b.z };
	}

	template<typename T>
	vec3Imp<bool> operator<=(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return { a.x <= b.x, a.y <= b.y, a.z <= b.z };
	}

	template<typename T>
	vec3Imp<bool> operator>(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return { a.x > b.x, a.y > b.y, a.z > b.z };
	}

	template<typename T>
	vec3Imp<bool> operator>=(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return { a.x >= b.x, a.y >= b.y, a.z >= b.z };
	}

	template<typename T>
	T dot(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return(a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	template<typename T>
	T mag(const vec3Imp<T>& v)
	{
		return T(std::sqrt(magSq(v)));
	}

	template<typename T>
	T magSq(const vec3Imp<T>& v)
	{
		return sq(v.x) + sq(v.y) + sq(v.z);
	}

	template<typename T>
	vec3Imp<T> normalize(const vec3Imp<T>& v)
	{
		return v / mag(v);
	}

	template<typename T>
	vec3Imp<T> abs(const vec3Imp<T>& v)
	{
		using std::abs;
		return { abs(v.x), abs(v.y), abs(v.z) };
	}

	template<typename T>
	vec3Imp<T> max(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		using std::max;
		return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) };
	}

	template<typename T>
	vec3Imp<T> min(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		using std::min;
		return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) };
	}

	template<typename T>
	vec3Imp<T> sin(const vec3Imp<T>& v)
	{
		using std::sin;
		return { sin(v.x), sin(v.y), sin(v.z) };
	}

	template<typename T>
	vec3Imp<T> cos(const vec3Imp<T>& v)
	{
		using std::cos;
		return { cos(v.x), cos(v.y), cos(v.z) };
	}

	template<typename T>
	vec3Imp<T> pow(const vec3Imp<T>& v, T p)
	{
		using std::pow;
		return { pow(v.x, p), pow(v.y, p), pow(v.z, p) };
	}

	template<typename T>
	vec3Imp<T> pow(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		using std::pow;
		return { pow(a.x, b.x), pow(a.y, b.y), pow(a.z, b.z) };
	}

	template<typename T>
	T dist(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return mag(a - b);
	}

	template<typename T>
	T distSq(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return magSq(a - b);
	}

	template<typename T>
	vec3Imp<T> cross(const vec3Imp<T>& a, const vec3Imp<T>& b)
	{
		return {
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x)
		};
	}

	template<typename T>
	vec3Imp<T> rotateX(const vec3Imp<T>& v, T theta)
	{
		using std::sin, std::cos;
		return {
			v.x,
			v.y * cos(theta) - v.z * sin(theta),
			v.y * sin(theta) + v.z * cos(theta)
		};
	}

	template<typename T>
	vec3Imp<T> rotateY(const vec3Imp<T>& v, T theta)
	{
		using std::sin, std::cos;
		return {
			v.x * cos(theta) + v.z * sin(theta),
			v.y,
			-v.x * sin(theta) + v.z * cos(theta)
		};
	}

	template<typename T>
	vec3Imp<T> rotateZ(const vec3Imp<T>& v, T theta)
	{
		using std::sin, std::cos;
		return {
			v.x * cos(theta) - v.y * sin(theta),
			v.x * sin(theta) - v.y * cos(theta),
			v.z
		};
	}

}

#endif /*!RAYCHEL_VEC3_IMP*/
