#include <catch2/catch.hpp>
#include <iostream>

#include "Raychel/Core/RaychelMath/Impl/QuaternionImpl.inl"
#include "Raychel/Core/RaychelMath/Impl/vec3Impl.inl"
#include "Raychel/Core/RaychelMath/Quaternion.h"

//clang-format doesn't like these macros
// clang-format off

#define RAYCHEL_QUATERNION_TEST_TYPES float, double, long double
#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                                                                  \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_QUATERNION_TEST_TYPES)                                                       \
    {                                                                                                                            \
        using namespace Raychel;                                                                                                 \
        using Quaternion = QuaternionImp<TestType>;                                                                              \
        using vec3 = vec3Imp<TestType>;                                              

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating Quaternions", "[RaychelMath][Quaternion]")

    const TestType one_over_sqrt2 = 1.0L / std::sqrt(2.0L);
    const TestType sin_eighth_pi = std::sin(quarterPi<long double> * 0.5L);
    const TestType cos_eighth_pi = std::cos(quarterPi<long double> * 0.5L);

    const Quaternion a{};
    const Quaternion b{12, 7, 19, 4};
    const Quaternion c{vec3{0, 1, 0}, 0.0};
    const Quaternion d{vec3{1, 0, 1}, halfPi<TestType>};
    const Quaternion e{vec3{-9, 12, 20}, quarterPi<TestType>}; //pythagorean quadruple mag 25

    REQUIRE(a.r == 1);
    REQUIRE(a.i == 0);
    REQUIRE(a.j == 0);
    REQUIRE(a.k == 0);

    REQUIRE(b.r == 12);
    REQUIRE(b.i == 7);
    REQUIRE(b.j == 19);
    REQUIRE(b.k == 4);

    REQUIRE(c.r == 1);
    REQUIRE(c.i == 0);
    REQUIRE(c.j == 0);
    REQUIRE(c.k == 0);

    REQUIRE(equivalent<TestType>(d.r, one_over_sqrt2));
    REQUIRE(equivalent<TestType>(d.i, 0.5)); 
    REQUIRE(d.j == 0); 
    REQUIRE(equivalent<TestType>(d.k, 0.5));

    REQUIRE(equivalent<TestType>(e.r, cos_eighth_pi));
    REQUIRE(equivalent<TestType>(e.i, -.36 * sin_eighth_pi)); 
    REQUIRE(equivalent<TestType>(e.j, .48 * sin_eighth_pi)); 
    REQUIRE(equivalent<TestType>(e.k, .8 * sin_eighth_pi));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion addition", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, 9, 14};

    const auto res = q + Quaternion{-5, 19, 3, -35};

    REQUIRE(res.r == 7);
    REQUIRE(res.i == 26);
    REQUIRE(res.j == 12);
    REQUIRE(res.k == -21);

    q += Quaternion{7, 4, -12, 9};

    REQUIRE(q.r == 19);
    REQUIRE(q.i == 11);
    REQUIRE(q.j == -3);
    REQUIRE(q.k == 23);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion subtraction", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, 9, 14};

    const auto res = q - Quaternion{-5, 19, 3, -35};

    REQUIRE(res.r == 17);
    REQUIRE(res.i == -12);
    REQUIRE(res.j == 6);
    REQUIRE(res.k == 49);

    q -= Quaternion{7, 4, -12, 9};

    REQUIRE(q.r == 5);
    REQUIRE(q.i == 3);
    REQUIRE(q.j == 21);
    REQUIRE(q.k == 5);

    const auto q2 = -q;

    REQUIRE(q2.r == -5);
    REQUIRE(q2.i == -3);
    REQUIRE(q2.j == -21);
    REQUIRE(q2.k == -5);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion multiplication: Quaternion", "[RaychelMath][Quaternion]")

    Quaternion a{12, 7, 9, 4};
    Quaternion b{-1, 0.5, 7, 113};

    const auto ab = a * b;

    REQUIRE(ab.r == -530.5);
    REQUIRE(ab.i == 988);
    REQUIRE(ab.j == -714);
    REQUIRE(ab.k == 1396.5);

    //Quaternion multiplication is non-commutative, so a * b != b * a
    const auto ba = b * a;

    REQUIRE(ba.r == -530.5);
    REQUIRE(ba.i == -990);
    REQUIRE(ba.j == 864);
    REQUIRE(ba.k == 1307.5);

    auto _a = a;
    auto _b = b;

    _a *= b;

    REQUIRE(_a.r == -530.5);
    REQUIRE(_a.i == 988);
    REQUIRE(_a.j == -714);
    REQUIRE(_a.k == 1396.5);

    _b *= a;

    REQUIRE(_b.r == -530.5);
    REQUIRE(_b.i == -990);
    REQUIRE(_b.j == 864);
    REQUIRE(_b.k == 1307.5);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion multiplication: Scalar", "[RaychelMath][Quaternion]")

    const TestType s = -0.5;
    Quaternion a{12, 7.5, -3, 9};

    const auto res = a * s;

    REQUIRE(res.r == -6);
    REQUIRE(res.i == -3.75);
    REQUIRE(res.j == 1.5);
    REQUIRE(res.k == -4.5);

    a *= s;

    REQUIRE(a.r == -6);
    REQUIRE(a.i == -3.75);
    REQUIRE(a.j == 1.5);
    REQUIRE(a.k == -4.5);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion multiplication: Vector", "[RaychelMath][Quaternion]")

    const vec3 x{1, 0, 0};
    const vec3 y{0, 1, 0};
    const vec3 z{0, 0, 1};

    const vec3 v{12.345, -7.99, 4};

    const Quaternion a{vec3{2, 0, -1}, pi<TestType>};

    const auto x_r = x * a;

    REQUIRE(equivalent<TestType>(x_r.x, 0.6));
    REQUIRE(equivalent<TestType>(x_r.y, 0));
    REQUIRE(equivalent<TestType>(x_r.z, -0.8));

    const auto y_r = y * a;

    REQUIRE(equivalent<TestType>(y_r.x, 0));
    REQUIRE(equivalent<TestType>(y_r.y, -1));
    REQUIRE(equivalent<TestType>(y_r.z, 0));

    const auto z_r = z * a;

    REQUIRE(equivalent<TestType>(z_r.x, -0.8));
    REQUIRE(equivalent<TestType>(z_r.y, 0));
    REQUIRE(equivalent<TestType>(z_r.z, -0.6));

    const auto v_r = v * a;

    REQUIRE(equivalent<TestType>(v_r.x, 4.207));
    REQUIRE(equivalent<TestType>(v_r.y, 7.99));
    REQUIRE(equivalent<TestType>(v_r.z, -12.276));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion division: Quaternion", "[RaychelMath][Quaternion]")
    
    Quaternion q{12, -4.5, -6, 9};
    const Quaternion b{1, 2, 3, 4};

    auto res = q / b;

    REQUIRE(equivalent<TestType>(res.r, 0.7));
    REQUIRE(equivalent<TestType>(res.i, 0.75));
    REQUIRE(equivalent<TestType>(res.j, -2.6));
    REQUIRE(equivalent<TestType>(res.k, -1.25));

    res = b / q;

    REQUIRE(equivalent<TestType>(res.r, 89.6/1200.0L));
    REQUIRE(equivalent<TestType>(res.i, -0.08));
    REQUIRE(equivalent<TestType>(res.j, 8.32/30.0L));
    REQUIRE(equivalent<TestType>(res.k, 4/30.0L));

    q /= b;

    REQUIRE(equivalent<TestType>(q.r, 0.7));
    REQUIRE(equivalent<TestType>(q.i, 0.75));
    REQUIRE(equivalent<TestType>(q.j, -2.6));
    REQUIRE(equivalent<TestType>(q.k, -1.25));

    res = b / b;

    REQUIRE(equivalent<TestType>(res.r, 1));
    REQUIRE(equivalent<TestType>(res.i, 0));
    REQUIRE(equivalent<TestType>(res.j, 0));
    REQUIRE(equivalent<TestType>(res.k, 0));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion division: scalar", "[RaychelMath][Quaternion]")

    Quaternion q{12, -4.5, -6, 9};
    const TestType s = 2;

    const auto res = q / s;

    REQUIRE(res.r == 6);
    REQUIRE(res.i == -2.25);
    REQUIRE(res.j == -3);
    REQUIRE(res.k == 4.5);

    q /= s;

    REQUIRE(q.r == 6);
    REQUIRE(q.i == -2.25);
    REQUIRE(q.j == -3);
    REQUIRE(q.k == 4.5);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion Comparison", "[RaychelMath][Quaternion]")

    constexpr Quaternion a{12, 7, 5, -17};
    Quaternion b = a;

    REQUIRE(a == b);
    REQUIRE(b == a);
    REQUIRE(!(a != b));
    REQUIRE(!(b != a));

    b = Quaternion{5, 9, 4, 0};

    REQUIRE(!(a == b));
    REQUIRE(!(b == a));
    REQUIRE(a != b);
    REQUIRE(b != a);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion dot product", "[RaychelMath][Quaternion]")

    Quaternion a{12, 9, 17, 4};
    Quaternion b = a;

    auto res = dot(a, b);

    REQUIRE(res == 530);
    REQUIRE(res == dot(b, a));

    b = -a;
    res = dot(a, b);

    REQUIRE(res == -530);
    REQUIRE(res == dot(b, a));

    a = Quaternion{0, 1, 0, 1};
    b = Quaternion{1, 0, 1, 0};

    REQUIRE(dot(a, b) == 0);
    REQUIRE(dot(b, a) == 0);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion magnitude", "[RaychelMath][Quaternion]")

    const auto sqrt_299 = std::sqrt(TestType{299});
    Quaternion q{12, 7, -9, 5};

    const auto res = mag(q);

    REQUIRE(res == sqrt_299);

    q = Quaternion{};

    REQUIRE(mag(q) == 1); //Yes, the default quaternion is normalized

    q = Quaternion{0, 0, 0, 0};

    REQUIRE(mag(q) == 0);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion magnitude squared", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, -9, 5};

    const auto res = magSq(q);

    REQUIRE(res == 299);

    q = Quaternion{};

    REQUIRE(magSq(q) == 1); //Yes, the default quaternion is normalized

    q = Quaternion{0, 0, 0, 0};

    REQUIRE(magSq(q) == 0);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion normalization", "[RaychelMath][Quaternion]")

    Quaternion q{1, 5, -7, 4};

    auto res = normalize(q);

    REQUIRE(equivalent<TestType>(mag(res), 1.0));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion conjugate", "[RaychelMath][Quaternion]")

    const Quaternion q{1, 0, -5, 9};
    const auto res = conjugate(q);

    REQUIRE(res.r == 1);
    REQUIRE(res.i == 0);
    REQUIRE(res.j == 5);
    REQUIRE(res.k == -9);

RAYCHEL_END_TEST

//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion inverse", "[RaychelMath][Quaternion]")

    const Quaternion q{12, -5, 17, 9};

    const TestType q_mag_sq = sq(q.r) + sq(q.i) + sq(q.j) + sq(q.k);
    const auto r =  q.r / q_mag_sq;
    const auto i = -q.i / q_mag_sq;
    const auto j = -q.j / q_mag_sq;
    const auto k = -q.k / q_mag_sq;

    const auto res = inverse(q);

    REQUIRE(equivalent<TestType>(res.r, r));
    REQUIRE(equivalent<TestType>(res.i, i));
    REQUIRE(equivalent<TestType>(res.j, j));
    REQUIRE(equivalent<TestType>(res.k, k));

RAYCHEL_END_TEST

//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion look_at", "[RaychelMath][Quaternion]")
    const vec3 forward{0, 0, 1};

    const vec3 origin{};
    const vec3 target{0, 0, 12};

    const auto dir = look_at(forward, target-origin);

    
RAYCHEL_END_TEST