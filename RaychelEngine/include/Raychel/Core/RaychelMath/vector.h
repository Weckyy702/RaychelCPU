/**
* \file vector.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Additional vector functions for RaychelMath
* \date 2021-07-07
* 
* MIT License
* Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
*/
#ifndef RAYCHEL_VECTOR_H
#define RAYCHEL_VECTOR_H

#include "Raychel/Core/RaychelMath/vec3.h"
#include <tuple>

namespace Raychel {

    /**
	*\brief Rotate the vector theta radians around positive X
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
    template <typename T, RAYCHEL_ENABLE_IF_FLOATING_POINT(T)>
    vec3Imp<T> rotateX(const vec3Imp<T>& v, T) noexcept;

    /**
	*\brief Rotate the vector theta radians around positive Y
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
    template <typename T, RAYCHEL_ENABLE_IF_FLOATING_POINT(T)>
    vec3Imp<T> rotateY(const vec3Imp<T>& v, T) noexcept;

    /**
	*\brief Rotate the vector theta radians around positive Z
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec3Imp<T> 
	*/
    template <typename T, RAYCHEL_ENABLE_IF_FLOATING_POINT(T)>
    vec3Imp<T> rotateZ(const vec3Imp<T>& v, T) noexcept;
    /**
	*\brief Reflect vector along normal
	*
	*\tparam T Type of the vector
	*\param dir direction to be reflected
	*\param normal normal to reflect around
	*\return vec3 the reflected vector
	*/
    template <typename T, RAYCHEL_ENABLE_IF_FLOATING_POINT(T)>
    constexpr vec3Imp<T> reflect(const vec3Imp<T>& dir, const vec3Imp<T>& normal) noexcept;

    /**
    * \brief Get the basis vectors around normal
    * 
    * \tparam T type of vector
    * \param normal +Y axis for the local coordinate frame
    * \return +x, +y, +z axis as a tuple
    */
    template<typename T, RAYCHEL_ENABLE_IF_FLOATING_POINT(T)>
    std::tuple<vec3Imp<T>, vec3Imp<T>, vec3Imp<T>> get_basis_vector(const vec3Imp<T>& normal) noexcept;

    /**
    * \brief Get a random direction on the hemisphere around normal
    * 
    * \tparam T type of vector
    * \tparam RNG_t type of RNG used to generate the random distribution
    * \param normal normal vector for the hemisphere
    * \return  
    */
    template<typename T, typename RNG_t, RAYCHEL_ENABLE_IF_FLOATING_POINT(T), typename = std::enable_if_t<std::is_invocable_r_v<T, RNG_t>>>
    vec3Imp<T> get_random_direction_on_hemisphere(const vec3Imp<T>& normal, const RNG_t&) noexcept;

    /**
    * \brief Get a random direction on a cone angle
    * 
    * \tparam T type of vector
    * \tparam RNG_t type of RNG used to generate the random distribution
    * \param normal normal of the cone
    * \param cone_angle angle between the normal and the cones sides
    * \return  
    */
    template<typename T, typename RNG_t, typename = std::enable_if_t<std::is_floating_point_v<T>>, typename = std::enable_if_t<std::is_invocable_r_v<T, RNG_t>>>
    vec3Imp<T> get_random_direction_on_cone_angle(const vec3Imp<T>& normal, T cone_angle, const RNG_t&) noexcept;
} // namespace Raychel

#endif //!RAYCHEL_VECTOR_H