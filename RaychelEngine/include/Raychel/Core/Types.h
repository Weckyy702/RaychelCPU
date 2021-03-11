#ifndef RAYCHEL_TYPES_H
#define RAYCHEL_TYPES_H
#pragma once

#include "utils.h"
#include "RaychelMath/vec2.h"
#include "RaychelMath/vec3.h"
#include "RaychelMath/color.h"
#include "RaychelMath/Quaternion.h"

namespace Raychel {

	//snice literal operators cannot be templated, this must be changed according to
	//the preferred floating point type
    using number_t = double;

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

    //all of the types below must use the same type argument in order to work together correctly
	using vec2 = vec2Imp<number_t>;
	using vec3 = vec3Imp<number_t>;
	using color = colorImp<number_t>;
	using Quaternion = QuaternionImp<number_t>;
}

#endif /*!RAYCHEL_TYPES_H*/
