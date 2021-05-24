#include "Raychel/Core/RaychelMath/Impl/colorImpl.inl"
#include "Raychel/Core/RaychelMath/color.h"
#include "Raychel/Core/utils.h"

#include <catch2/catch.hpp>
#include <cstddef>
#include <type_traits>

// these are common types for colors
#define RAYCHEL_TEST_TYPES unsigned char, size_t, float, double

#define RAYCHEL_BEGIN_TEST(name, tag)                                          \
    TEMPLATE_TEST_CASE(name, tag, RAYCHEL_TEST_TYPES)                          \
    {                                                                          \
        using namespace Raychel;                                               \
        using color = colorImp<TestType>;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating colors", "[RaychelMath]")
    const color c{1, 0, 124};
    REQUIRE(c.r == 1);
    REQUIRE(c.g == 0);
    REQUIRE(c.b == 124);

    const color c2{1, 2};
    REQUIRE(c2.r == 1);
    REQUIRE(c2.g == 2);
    REQUIRE(c2.b == 0);

    const color c3{1};
    REQUIRE(c3.r == 1);
    REQUIRE(c3.g == 1);
    REQUIRE(c3.b == 1);

    const color c4 = c3;
    REQUIRE(c4.r == c3.r);
    REQUIRE(c4.g == c3.g);
    REQUIRE(c4.b == c3.b);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color addition", "[RaychelMath]")
    const color c{1, 1, 1};

    const color c2 = c + color{0, 1, 5};

    REQUIRE(c2.r == 1);
    REQUIRE(c2.g == 2);
    REQUIRE(c2.b == 6);

    color c3{1, 1, 1};
    c3 += color{0, 1, 5};

    REQUIRE(c3.r == 1);
    REQUIRE(c3.g == 2);
    REQUIRE(c3.b == 6);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color subtraction", "[RaychelMath]")
    const color c{128};

    const auto res = c - color{64, 128, 5};

    REQUIRE(res.r == 64);
    REQUIRE(res.g == 0);
    REQUIRE(res.b == 123);

    color c2{128};
    c2 -= color{64, 128, 5};

    REQUIRE(c2.r == 64);
    REQUIRE(c2.g == 0);
    REQUIRE(c2.b == 123);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color multiplication", "[RaychelMath]")
    const color c{12};

    color res = c * color{5, 0, 2};
    REQUIRE(res.r == 60);
    REQUIRE(res.g == 0);
    REQUIRE(res.b == 24);


    res = c * TestType{2};
    REQUIRE(res.r == 24);
    REQUIRE(res.g == 24);
    REQUIRE(res.b == 24);

    if constexpr (std::is_floating_point_v<TestType>) {
        const color c1{1, 0, .5};

        res = c1 * color{0.5, 0.25, 2.5};

        REQUIRE(res.r == 0.5);
        REQUIRE(res.g == 0);
        REQUIRE(res.b == 1.25);


        res = c1 * TestType{0.5};

        REQUIRE(res.r == 0.5);
        REQUIRE(res.g == 0);
        REQUIRE(res.b == .25);
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color comparison: equality", "[RaychelMath]")

    const color c{1, 12, 5};

    REQUIRE(c == c);
    REQUIRE(c == color{1, 12, 5});

    REQUIRE(c != color{0, 5, 42});

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color comparison: greater than", "[RaychelMath]")

    const color c{0, 12, 3};
    const color comp{1, 7, 3};

    const auto greater_than = c > comp;

    REQUIRE(greater_than.r == false);
    REQUIRE(greater_than.g == true);
    REQUIRE(greater_than.b == false);

    const auto greater_than_or_equal = c >= comp;

    REQUIRE(greater_than_or_equal.r == false);
    REQUIRE(greater_than_or_equal.g == true);
    REQUIRE(greater_than_or_equal.b == true);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color comparison: less than", "[RaychelMath]")

    const color c{0, 12, 3};
    const color comp{1, 7, 3};

    const auto less_than = c < comp;

    REQUIRE(less_than.r == true);
    REQUIRE(less_than.g == false);
    REQUIRE(less_than.b == false);

    const auto less_than_or_equal = c <= comp;

    REQUIRE(less_than_or_equal.r == true);
    REQUIRE(less_than_or_equal.g == false);
    REQUIRE(less_than_or_equal.b == true);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color max/min", "[RaychelMath]")

    const color c1{1, 7, 12};
    const color c2{0, 42, 9};

    color res = max(c1, c2);

    REQUIRE(res.r == 1);
    REQUIRE(res.g == 42);
    REQUIRE(res.b == 12);

    res = min(c1, c2);

    REQUIRE(res.r == 0);
    REQUIRE(res.g == 7);
    REQUIRE(res.b == 9);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color brightness", "[RaychelMath]")

    const color c{3, 4, 5};
    const auto b = brightness(c);

    REQUIRE(b == 4);

RAYCHEL_END_TEST