#ifndef RAYCHEL_QUATERNION_H
#define RAYCHEL_QUATERNION_H
#pragma once

#include "../utils.h"

namespace Raychel {

	template<RAYCHEL_NUMBER _number>
	class QuaternionImp {
	public:
		using value_type = std::remove_reference_t<std::remove_cv_t<_number>>;

	private:
		RAYCHEL_ENSURE_NUMBER(value_type, "Raychel::Quaternion<T> requires T to be of arithmetic type!");
		using vec3 = vec3Imp<value_type>;

	public:


		QuaternionImp()=default;

		QuaternionImp(value_type _r, value_type _i, value_type _j, value_type _k)
            :r{_r}, i{_i}, j{_j}, k{_k}
        {}

        QuaternionImp(const vec3&, value_type);

        inline vec3 v() const {
            return {i, j, k};
        }

        inline value_type s() const {
            return r;
        }

        QuaternionImp& operator+=(const QuaternionImp&);
        QuaternionImp& operator-=(const QuaternionImp&);
        QuaternionImp& operator*=(value_type);
        QuaternionImp& operator*=(const QuaternionImp&);
        QuaternionImp& operator/=(value_type);

        value_type r, i, j, k;
	};

	template<typename T>
	QuaternionImp<T> operator+(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator-(const QuaternionImp<T>&, const QuaternionImp<T>&);

	template<typename T>
	QuaternionImp<T> operator*(const QuaternionImp<T>&, const QuaternionImp<T>&);

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

}

#endif /*!RAYCHEL_QUATERNION_H*/
