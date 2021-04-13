/**
*\file Types.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for common types used within the engine
*\date 2021-03-24
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
#ifndef RAYCHEL_TYPES_H
#define RAYCHEL_TYPES_H
#pragma once

#include <memory>

#include "utils.h"
#include "RaychelMath/vec2.h"
#include "RaychelMath/vec3.h"
#include "RaychelMath/color.h"
#include "RaychelMath/Quaternion.h"
#include "RaychelMath/Transform.h"
#include "Forward.h"

namespace Raychel {

	//snice literal operators cannot be templated, this must be changed according to
	//the preferred floating point type
    using number_t = float;

	constexpr number_t operator "" _deg(long double x)
	{
        return number_t(x * degToRad<long double>);
	}

	constexpr number_t operator "" _deg(unsigned long long int x)
	{
	    return number_t(x * degToRad<long double>);
	}


	constexpr number_t operator "" _rad(unsigned long long int x)
	{
		return number_t(x);
	}
	//explicitly declare number as referring to radians
	constexpr number_t operator "" _rad(long double x)
	{
        return number_t(x);
	}

	//integral vector types
	using vec2i = vec2Imp<size_t>;

    //all of the types below must use the same type argument in order to work together correctly
	using vec2 = vec2Imp<number_t>;
	using vec3 = vec3Imp<number_t>;
	using color = colorImp<number_t>;
	using Quaternion = QuaternionImp<number_t>;
	using Transform = TransformImp<number_t>;

	using IRaymarchable_p = not_null<IRaymarchable*>;
	using IMaterial_p = std::unique_ptr<IMaterial>;


	extern const vec3 g_forward;
	extern const vec3 g_up;
	extern const vec3 g_right;
}

//Implementations
#include "RaychelMath/Impl/vec2Impl.inl"
#include "RaychelMath/Impl/vec3Impl.inl"
#include "RaychelMath/Impl/colorImpl.inl"
#include "RaychelMath/Impl/QuaternionImpl.inl"
#include "RaychelMath/Impl/TransformImpl.inl"

#endif /*!RAYCHEL_TYPES_H*/
