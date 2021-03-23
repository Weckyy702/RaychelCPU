#ifndef RAYCHEL_VEC3_H
#define RAYCHEL_VEC3_H
#pragma once

#include "../utils.h"

namespace Raychel {

	//3-dimensional vector
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

		template<typename To>
		constexpr vec3Imp<To> to() const;

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

	template<typename T>
	//rotate v around the positive y-axis ({1, 0, 0})
	//theta in radians
	vec3Imp<T> rotateX(const vec3Imp<T>& v, T theta);

	template<typename T>
	//rotate v around the positive y-axis ({0, 1, 0})
	//theta in radians
	vec3Imp<T> rotateY(const vec3Imp<T>& v, T theta);

	template<typename T>
	//rotate v around the positive y-axis ({0, 0, 1})
	//theta in radians
	vec3Imp<T> rotateZ(const vec3Imp<T>&, T theta);

	template<typename T>
	vec3Imp<T> sq(const vec3Imp<T>& v) {
		return v * v;
	}
}

#endif /*!RAYCHEL_VEC3_H*/
