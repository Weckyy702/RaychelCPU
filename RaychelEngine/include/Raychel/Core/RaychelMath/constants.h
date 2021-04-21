/**
*\file constants.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for mathematical constants
*\date 2021-03-23
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
#ifndef RAYCHEL_CONSTANTS_H
#define RAYCHEL_CONSTANTS_H

namespace Raychel {
	template<typename _float = float>
	constexpr _float pi = _float(3.14159265358979323846264);

	template<typename _float = float>
	constexpr _float twoPi = 2 * pi<_float>;

	template<typename _float = float>
	constexpr _float halfPi = 0.5 * pi<_float>;

	template<typename _float = float>
	constexpr _float quarterPi = 0.25 * pi<_float>;

	template<typename _float = float>
	constexpr _float degToRad = pi<_float> / 180;

	template<typename _float = float>
	constexpr _float radToDeg = 180 / pi<_float>;

	template<typename _float = float>
	constexpr _float e = _float(2.718281828459045235360287);

}

#endif /*!RAYCHEL_CONSTANTS_H*/
