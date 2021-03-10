#ifndef RAYCHEL_COLOR_H
#define RAYCHEL_COLOR_H
#pragma once

#include "../utils.h"

namespace Raychel {

	//RGB color
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

		//for use with function which expect an rgb* such as most OpenGL functions
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
	colorImp<bool> operator==(const colorImp<T>&, const colorImp<T>&);

	template<typename T>
	colorImp<bool> operator!=(const colorImp<T>&, const colorImp<T>&);

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
