/**
*\file utils.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Utility and core Header file
*\date 2021-03-25
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
#ifndef RAYCHEL_CORE_H
#define RAYCHEL_CORE_H
#pragma once

#if !defined(__cplusplus) || __cplusplus < 201703L
    #error "C++(17) compilation is required!"
#endif

#include <gsl/gsl>
#include <cstddef>
#include <type_traits>
#include <cmath>
#include <cassert>

//convenience headers
#include <memory>
#include <utility>
#include <vector>
#include <optional>

#include "Logger.h"
#include "RaychelMath/constants.h"

#if __has_cpp_attribute(__cpp_concepts) >= 201907L
#include <concepts>
namespace Raychel {
	template<typename T>
	concept arithmetic = std::integral<T> || std::floating_point<T>;
}
#define RAYCHEL_NUMBER arithmetic
#define RAYCHEL_ENSURE_NUMBER(t_arg, msg)

#else

#define RAYCHEL_NUMBER typename
#define RAYCHEL_ENSURE_NUMBER(t_arg, msg) static_assert(std::is_arithmetic_v<t_arg>, msg)

#endif

#ifndef NDEBUG
	#define RAYCHEL_DEBUG
#endif

#ifdef RAYCHEL_DEBUG
	#define RAYCHEL_LOG(...) Logger::debug( __PRETTY_FUNCTION__, ": ", __VA_ARGS__, '\n');
#else
	#define RAYCHEL_LOG(...)
#endif

//terminate the application with the provided message
#define RAYCHEL_TERMINATE(...) Logger::fatal( __PRETTY_FUNCTION__, "(", __FILE__, " : ", __LINE__, "): ", __VA_ARGS__, '\n');	\
								std::exit(0x41);

#if defined(RAYCHEL_DEBUG) || !defined(NDEBUG)
	#define RAYCHEL_ASSERT(exp) assert(exp);
#else
	#define RAYCHEL_ASSERT(exp)
#endif

//#define RAYCHEL_LOGICALLY_EQUAL //<-- activates logical equivalency for vector-like types

#define RAYCHEL_THROW_EXCEPTION(exception_type, msg, fatal) { \
				static_assert(std::is_base_of_v<::Raychel::exception_context, exception_type>, "Raychel exceptions must be derived from Raychel::exception_context!"); \
				throw ::Raychel::exception_type{msg, __PRETTY_FUNCTION__, fatal}; \
			}

namespace Raychel {

	using gsl::byte, gsl::not_null;
	using std::size_t;

	template<RAYCHEL_NUMBER _num>
	struct vec2Imp;
	template<RAYCHEL_NUMBER _num>
	struct vec3Imp;
	template<RAYCHEL_NUMBER _num>
	struct colorImp;
	template<RAYCHEL_NUMBER _num>
	struct QuaternionImp;
	template<RAYCHEL_NUMBER _num>
	struct TransformImp;

	struct exception_context {
		exception_context(const char* _msg, const char* _originFunc, bool _fatal)
			:what(_msg), originFunction(_originFunc), fatal(_fatal)
		{}

		exception_context(const exception_context& rhs)
			:what{rhs.what}, originFunction{rhs.originFunction}, fatal{rhs.fatal}
		{}

		const gsl::czstring<> what;
		const gsl::czstring<> originFunction;
		const bool fatal;
	};

	template<RAYCHEL_NUMBER _number>
	constexpr _number sq(_number x) {
		RAYCHEL_ENSURE_NUMBER(_number, "Raychel::sq<T> requires T to be of arithmetic type!");
		return x * x;
	}

	/**
	*\brief Linearly interpolate between two numbers
	*
	*\tparam _number Type of number to interpolate. Must be arithmetic
	*\param a first number (x=0.0)
	*\param b second number (x=1.0)
	*\param x value of interpolation
	*\return _number
	*/
	template<typename _number, typename = std::enable_if_t<std::is_arithmetic_v<_number>>>
	constexpr _number lerp(_number a, _number b, long double x)
	{
		return (x * b) + ((1.0-x) * a);
	}

	template<typename _integral>
	constexpr _integral bit(size_t shift) {
		static_assert(std::is_integral_v<_integral>, "Raychel::bit<T> requires T to be of integral type!");
		return static_cast<_integral>( 1 << shift);
	}

	/**
	*\brief Get number of digits in a number
	*
	*\param num The number with its digits
	*\return constexpr int 
	*/
	constexpr int numDigits(unsigned long long num, unsigned int base = 10)
	{
    	int digits = 0;

    	do {
        	digits++;
        	num /= base;
    	}while(num != 0);

		return digits;
	}

#if 0
	constexpr double abs(double x)
	{
		uint64_t rep = *reinterpret_cast<uint64_t*>(&x);
		rep &= 0x7fffffffffffffff;
		return *reinterpret_cast<double*>(&rep);
	}

	///\brief Return wether two floating point numbers are logically equivalent
	template<typename _float>
	constexpr bool equivalent(_float a, _float b)
	{
		static_assert(std::is_floating_point_v<_float>, "Raychel::equivalent<T> requires T to be a floating-point type!");

		constexpr _float epsilon = std::numeric_limits<_float>::epsilon() * 5;

		const auto min = std::min(a, b);

		const auto diff = std::abs(a-b);

		auto e = epsilon;
		if(min != 0)
			e = std::abs(min) * epsilon;

		const bool is_equal = a == b;
		const bool is_equivalent = diff < e;

		return  is_equal || is_equivalent;
	}
#endif

}

#endif // !RAYCHEL_CORE_H
