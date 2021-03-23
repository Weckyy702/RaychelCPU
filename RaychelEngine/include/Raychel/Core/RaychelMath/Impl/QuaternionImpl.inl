#ifndef RAYCHEL_QUATERNION_IMP
#define RAYCHEL_QUATERNION_IMP
#pragma once

#include "../Quaternion.h"
#include "../vec3.h"

namespace Raychel {

    template<typename T>
    QuaternionImp<T>::QuaternionImp(const vec3& _axis, value_type angle)
    {
        using std::sin, std::cos;

        const vec3 axis = -normalize(_axis);
        const auto s = sin(angle * 0.5);

        i = axis.x * s;
        j = axis.y * s;
        k = axis.z * s;

        r = cos(angle * 0.5);
    }

    template<typename T>
    QuaternionImp<T>& QuaternionImp<T>::operator+=(const QuaternionImp& q) {
        r += q.r;
        i += q.i;
        j += q.j;
        k += q.k;

        return *this;
    }

    template<typename T>
    QuaternionImp<T>& QuaternionImp<T>::operator-=(const QuaternionImp& q) {
        r -= q.r;
        i -= q.i;
        j -= q.j;
        k -= q.k;

        return *this;
    }

    template<typename T>
    QuaternionImp<T>& QuaternionImp<T>::operator*=(value_type s)
    {
        r *= s;
        i *= s;
        j *= s;
        k *= s;

        return *this;
    }

    template<typename T>
    QuaternionImp<T>& QuaternionImp<T>::operator*=(const QuaternionImp<T>& q)
    {
        value_type _r = r, _i = i, _j = j, _k = k;

        r = _r*q.r - _i*q.i - _j*q.j - _k*q.k;
        i = _r*q.i + _i*q.r + _j*q.k - _k*q.j;
        j = _r*q.j - _i*q.k + _j*q.r + _k*q.i;
        k = _r*q.k + _i*q.j - _j*q.i + _k*q.r;

        return *this;
    }

    template<typename T>
    QuaternionImp<T>& QuaternionImp<T>::operator/=(value_type s)
    {
        r /= s;
        i /= s;
        j /= s;
        k /= s;

        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const QuaternionImp<T>& obj)
    {
        return os << "{ " << obj.r << ", " << obj.i << ", " << obj.j << ", " << obj.k << " }";
    }

    template<typename T>
	QuaternionImp<T> operator+(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
        return { a.r+b.r, a.i+b.i, a.j+b.j, a.k+b.k };
	}

    template<typename T>
	QuaternionImp<T> operator-(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
        return { a.r - b.r, a.i - b.i, a.j - b.j, a.k - b.k };
	}

    template<typename T>
	QuaternionImp<T> operator*(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
        auto r = a.r*b.r - a.i*b.i - a.j*b.j - a.k*b.k;
        auto i = a.r*b.i + a.i*b.r + a.j*b.k - a.k*b.j;
        auto j = a.r*b.j - a.i*b.k + a.j*b.r + a.k*b.i;
        auto k = a.r*b.k + a.i*b.j - a.j*b.i + a.k*b.r;

        return { r, i, j, k };
	}

    template<typename T>
	vec3Imp<T> operator*(const vec3Imp<T>& _v, const QuaternionImp<T>& _q)
	{
        auto q = normalize(_q);
        auto p = QuaternionImp<T>(0.0, _v.x, _v.y, _v.z);

        return (q*p*conjugate(q)).v();
	}

    template<typename T>
	QuaternionImp<T> operator*(const QuaternionImp<T>& q, T s)
	{
        return {q.r*s, q.i*s, q.j*s, q.k*s};
	}

	template<typename T>
	QuaternionImp<T> operator/ (const QuaternionImp<T>& q, T s)
	{
        return {q.r / s, q.i / s, q.j / s, q.k / s};
	}

    template<typename T>
	bool operator==(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
#ifdef RAYCHEL_LOGICALLY_EQUAL
        return equivalent(a.r, b.r) && equivalent(a.i, b.i) && equivalent(a.j, b.j) && equivalent(a.k, b.k);
#else
        return (a.r == b.r) && (a.i == b.i) && (a.j == b.j) && (a.k == b.k);
#endif
	}

    template<typename T>
	T dot(const QuaternionImp<T>& a, const QuaternionImp<T>& b)
	{
        return a.r*b.r + a.i*b.i + a.j*b.j + a.k*b.k;
	}

    template<typename T>
	T mag(const QuaternionImp<T>& q)
	{
        return std::sqrt(sq(q.r) + sq(q.i) + sq(q.j) + sq(q.k));
	}

    template<typename T>
	T magSq(const QuaternionImp<T>& q)
	{
        return sq(q.r) + sq(q.i) + sq(q.j) + sq(q.k);
	}

    template<typename T>
	QuaternionImp<T> normalize(const QuaternionImp<T>& q)
	{
	    return q / mag(q);
	}

    template<typename T>
	QuaternionImp<T> conjugate(const QuaternionImp<T>& q)
	{
        return { q.r, -q.i, -q.j, -q.k };
	}

    template<typename T>
	QuaternionImp<T> inverse(const QuaternionImp<T>& q)
	{
        return conjugate(q) / magSq(q);
	}

}

#endif // RAYCHEL_QUATERNION_IMP
