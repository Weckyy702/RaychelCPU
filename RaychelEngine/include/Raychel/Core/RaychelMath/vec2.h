#ifndef RAYCHEL_VEC2_H
#define RAYCHEL_VEC2_H
#pragma once

#include "../utils.h"

namespace Raychel {

	//2-dimensional vector
	template<RAYCHEL_NUMBER _number>
	struct vec2Imp {

		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:

		RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::vec2<T> requires T to be of atithmetic type!");

		using vec3 = vec3Imp<value_type>;
		using color = colorImp<value_type>;

	public:

		vec2Imp() = default;

		explicit vec2Imp(value_type _x)
			:x(_x), y(0)
		{}

		vec2Imp(value_type _x, value_type _y)
			:x(_x), y(_y)
		{}

		explicit vec2Imp(const vec3&);
		explicit vec2Imp(const color&);

		vec2Imp& operator=(const vec3&);
		vec2Imp& operator=(const color&);

		vec2Imp& operator+=(const vec2Imp&);
		vec2Imp& operator-=(const vec2Imp&);
		vec2Imp& operator*=(value_type);
		vec2Imp& operator*=(const vec2Imp&);
		vec2Imp& operator/=(value_type);
		vec2Imp& operator/=(const vec2Imp&);
		vec2Imp& operator%=(const vec2Imp&);

		value_type x= value_type(0), y= value_type(0);
	};

	template<typename T>
	vec2Imp<T> operator-(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> operator+(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> operator-(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> operator*(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> operator*(const vec2Imp<T>&, T);

	template<typename T>
	inline vec2Imp<T> operator*(T s, const vec2Imp<T>& v)
	{
		return v * s;
	}

	template<typename T>
	vec2Imp<T> operator/(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> operator/(const vec2Imp<T>&, T);

	template<typename T>
	vec2Imp<T> operator%(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	bool operator==(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	bool operator!=(const vec2Imp<T>& a, const vec2Imp<T>& b)
	{
		return !(a == b);
	}

	template<typename T>
	vec2Imp<bool> operator==(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<bool> operator!=(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<bool> operator<(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<bool> operator<=(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<bool> operator>(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<bool> operator>=(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	T dot(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	T mag(const vec2Imp<T>&);

	template<typename T>
	T magSq(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> normalize(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> abs(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> max(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> min(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> sin(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> cos(const vec2Imp<T>&);

	template<typename T>
	vec2Imp<T> pow(const vec2Imp<T>&, T);

	template<typename T>
	vec2Imp<T> pow(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	T dist(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	T distSq(const vec2Imp<T>&, const vec2Imp<T>&);

	template<typename T>
	//rotate v on the xy-plane
	//theta in radians
	vec2Imp<T> rotate(const vec2Imp<T>& v, T theta);
}

#endif // !RAYCHEL_VEC2_H
