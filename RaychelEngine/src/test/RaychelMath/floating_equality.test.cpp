#include <catch2/catch.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "Logger.h"
#include "Raychel/Core/RaychelMath/equivalent.h"

//clang-format doesn't like these macros
// clang-format off

#define RAYCHEL_BEGIN_TEST(test_name, test_tag) TEMPLATE_TEST_CASE(test_name, test_tag, float, double, long double) \
{   \
    using namespace Raychel;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: 'normal' values", "[RaychelMath][Float]")

    TestType f = 0.1;

    TestType a = 0;
    for(int i = 0; i < 10; i++) {
        a += f;
    }

    Logger::log(__FUNCTION__, '\n');

    TestType b = f * 10;

    std::cout << std::setprecision(100) 
    << a << '\n'
    << b << '\n'
    << 10*f << '\n'
    << TestType(1.0) << '\n';

    REQUIRE(equivalent<TestType>(a, 1.0L));
    REQUIRE(equivalent<TestType>(b, 1.0L));
    REQUIRE(equivalent<TestType>(10*f, 1.0L));
    REQUIRE(equivalent(a, b)); //this is technically wrong, but if equivalency is arithmetic, so a = c  b = c => a = b

    f = 100;

    a = 0; 
    for(int i = 0; i < 10; i++) {
        a += f;
    }

    b = f * 10;

    REQUIRE(equivalent<TestType>(a, 1000));
    REQUIRE(equivalent<TestType>(b, 1000));

    REQUIRE(equivalent<TestType>(a, b));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: very huge values", "[RaychelMath][Float]")

    const TestType f = 1.234e35;

    TestType a = 0;
    for(int i = 0; i < 10; i++) {
        a += f;
    }

    const TestType b = f * 10;

    std::cout << std::setprecision(100) 
    << a << '\n'
    << b << '\n'
    << 10*f << '\n'
    << TestType(1.234e36L) << '\n';

    Logger::log(__FUNCTION__, '\n');

    REQUIRE(equivalent<TestType>(a, 1.234e36L));
    REQUIRE(equivalent<TestType>(b, 1.234e36L));
    REQUIRE(equivalent<TestType>(10*f, 1.234e36L));
    REQUIRE(equivalent(a, b)); //this is technically wrong, but if equivalency is arithmetic, so a = c  b = c => a = b

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: very tiny values", "[RaychelMath][Float]")

    const TestType f = 1.234e-7;

    TestType a = 0;
    for(int i = 0; i < 10; i++) {
        a += f;
    }

    Logger::log(__FUNCTION__, '\n');

    const TestType b = f * 10;

    REQUIRE(equivalent<TestType>(a, 1.234e-6));
    REQUIRE(equivalent<TestType>(b, 1.234e-6));
    REQUIRE(equivalent<TestType>(10*f, 1.234e-6));
    REQUIRE(equivalent(a, b)); //this is technically wrong, but if equivalency is arithmetic, so a = c  b = c => a = b

    REQUIRE(equivalent<TestType>(1e-30, 0.0));
    REQUIRE(equivalent<TestType>(1e-30, -0.0));
    REQUIRE(equivalent<TestType>(-1e-30, 0.0));
    REQUIRE(equivalent<TestType>(-1e-30, -0.0L));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: sanity checks", "[RaychelMath][Float]")

    REQUIRE(!equivalent<TestType>(1.0, 1.1));
    REQUIRE(!equivalent<TestType>(1.0, 1.05));
    REQUIRE(!equivalent<TestType>(1.0, 1.01));

    REQUIRE(!equivalent<TestType>(0.25, 0.2));

    REQUIRE(!equivalent<TestType>(1e10, 1.5e10));
    REQUIRE(!equivalent<TestType>(1e10, 1.1e10));
    REQUIRE(!equivalent<TestType>(1e10, 1.05e10));
    REQUIRE(!equivalent<TestType>(1e10, 1.005e10));

    REQUIRE(!equivalent(-1e-10, 1e-10));
    REQUIRE(!equivalent(1e-5, 1.5e-5));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: zeroes", "[RaychelMath][Float]")

    REQUIRE(equivalent<TestType>(0.0, -0.0));

    const TestType f = 0.1;

    REQUIRE(equivalent<TestType>(f - f, 0.0));
    REQUIRE(equivalent<TestType>((1000*f) - (f*1000), 0.0));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: infinities", "[RaychelMath][Float]")

    constexpr auto infinity = std::numeric_limits<TestType>::infinity();
    constexpr auto neg_infinity = -std::numeric_limits<TestType>::infinity();

    REQUIRE(equivalent<TestType>(infinity, infinity));

    REQUIRE(equivalent<TestType>(infinity, 1 / TestType(0)));
    REQUIRE(equivalent<TestType>(neg_infinity, 1 / TestType(-0.0)));

    REQUIRE(equivalent<TestType>(std::log(TestType(0)), neg_infinity));

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Floating point equality: NaN", "[RaychelMath][Float]")

    REQUIRE(!equivalent<TestType>(std::numeric_limits<TestType>::quiet_NaN(), 0));
    REQUIRE(!equivalent<TestType>(std::numeric_limits<TestType>::quiet_NaN(), std::numeric_limits<TestType>::quiet_NaN())); //NaN != NaN, yes this is right
    REQUIRE(!equivalent<TestType>(std::numeric_limits<TestType>::quiet_NaN(), std::numeric_limits<TestType>::infinity()));
    REQUIRE(!equivalent<TestType>(std::numeric_limits<TestType>::quiet_NaN(), std::numeric_limits<TestType>::signaling_NaN()));

RAYCHEL_END_TEST