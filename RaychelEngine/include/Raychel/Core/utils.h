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

#if !((defined(__cplusplus) && __cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L))
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

#include "CMakeSettings.h"
#include "RaychelMath/constants.h"
#include "Logger.h"

#if defined(__clang__) || defined(__GNUC__)
	#define RAYCHEL_FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
	#define RAYCHEL_FUNC_NAME __FUNCSIG__
#else
	#error "Unknown compiler detected!"
#endif

#ifdef RAYCHEL_DEBUG
	#define RAYCHEL_LOG(...) Logger::debug( RAYCHEL_FUNC_NAME, ": ", __VA_ARGS__, '\n');
#else
	#define RAYCHEL_LOG(...)
#endif

//terminate the application with the provided message
#ifndef RAYCHEL_NO_LOGGER
#define RAYCHEL_TERMINATE(...) Logger::fatal( RAYCHEL_FUNC_NAME, " at (", __FILE__, ":", __LINE__, "): ", __VA_ARGS__, '\n');	\
								std::exit(0x41);
#else
#define RAYCHEL_TERMINATE(...) std::exit(0x41);
#endif

#if defined(RAYCHEL_DEBUG) || !defined(NDEBUG)
	#define RAYCHEL_ASSERT(exp) if(!(exp)) { \
		RAYCHEL_TERMINATE("Assertion '", GSL_STRINGIFY(exp), "' failed!");\
	}
#else
	#define RAYCHEL_ASSERT(exp) Expects(exp)
#endif

#define RAYCHEL_ASSERT_NOT_REACHED RAYCHEL_TERMINATE("Assertion failed! Expected to not execute ", __FILE__, ":", __LINE__)

//#define RAYCHEL_LOGICALLY_EQUAL //<-- activates logical equivalency for vector-like types

#define RAYCHEL_THROW_EXCEPTION(msg, fatal) { \
				throw ::Raychel::exception_context{msg, RAYCHEL_FUNC_NAME, fatal}; \
			}

#define RAYCHEL_ASSERT_NORMALIZED(vec) RAYCHEL_ASSERT(equivalent(magSq(vec), 1.0f));

namespace Raychel {

	using gsl::byte, gsl::not_null;
	using std::size_t;

	template<typename _num>
	struct vec2Imp;
	template<typename _num>
	struct vec3Imp;
	template<typename _num>
	struct colorImp;
	/*TODO: implement
	template<typename _num>
	class colorAlphaImp;
	*/
	template<typename _num>
	class QuaternionImp;
	template<typename _num>
	struct TransformImp;

	template<typename _number>
	constexpr _number sq(_number x) {
		static_assert(std::is_arithmetic_v<_number>, "Raychel::sq<T> requires T to be of arithmetic type!");
		return x * x;
	}

	/**
	*\brief Linearly interpolate between two numbers
	*
	*\tparam _number Type of number to interpolate. Must be arithmetic
	*\param a first number (x=0.0)
	*\param b second number (x=1.0)
	*\param x value of interpolation
	*\return _number the interpolated number
	*/
	template<typename _number>
	constexpr _number lerp(_number a, _number b, long double x)
	{
		return (x * b) + ((1.0-x) * a);
	}

	template<typename _integral>
	constexpr _integral bit(size_t shift) {
		static_assert(std::is_integral_v<_integral>, "Raychel::bit<T> requires T to be of integral type!");
		return static_cast<_integral>( 1U << shift);
	}

	/**
	*\brief Get number of digits in a number
	*
	*\param num The number with its digits
	*\return constexpr int 
	*/
	constexpr int numDigits(unsigned long long num, unsigned int base = 10U)
	{
		int digits = 0;

		do {
			digits++;
			num /= base;
		}while(num != 0);

		return digits;
	}

	///\brief Return wether two floating point numbers are logically equivalent
	template<typename _float>
	constexpr bool equivalent(_float a, _float b)
	{
		static_assert(std::is_floating_point_v<_float>, "Raychel::equivalent<T> requires T to be a floating-point type!");

		constexpr _float epsilon = std::numeric_limits<_float>::epsilon() * 5;

		const auto min = std::min(a, b);

		const auto diff = std::abs(a-b);

		auto eps = epsilon;
		if(min != 0)
			eps = std::abs(min) * epsilon;

		const bool is_equal = (a == b);

		return  is_equal || (diff < eps);
	}

}

#endif // !RAYCHEL_CORE_H
