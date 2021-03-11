#ifndef RAYCHEL_CONSTANTS_H
#define RAYCHEL_CONSTANTS_H
#pragma once

namespace Raychel {
	template<typename _float = double>
	constexpr _float pi = _float(3.14159265358979323846264);

	template<typename _float = double>
	constexpr _float twoPi = 2 * pi<_float>;

	template<typename _float = double>
	constexpr _float halfPi = 0.5 * pi<_float>;

	template<typename _float = double>
	constexpr _float quarterPi = 0.25 * pi<_float>;

	template<typename _float = double>
	constexpr _float degToRad = pi<_float> / 180;

	template<typename _float = double>
	constexpr _float radToDeg = 180 / pi<_float>;

	template<typename _float = double>
	constexpr _float e = _float(2.718281828459045235360287);

}

#endif /*!RAYCHEL_CONSTANTS_H*/
