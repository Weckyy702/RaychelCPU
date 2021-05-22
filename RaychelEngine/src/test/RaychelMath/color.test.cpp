#include "Raychel/Core/RaychelMath/Impl/colorImpl.inl"
#include "Raychel/Core/utils.h"

#include <catch2/catch.hpp>
#include <cstddef>

// these are common types for colors
#define RAYCHEL_TEST_TYPES unsigned char, size_t, float, double

#define RAYCHEL_BEGIN_TEST(name, tag)                                          \
    TEMPLATE_TEST_CASE(name, tag, RAYCHEL_TEST_TYPES) {                        \
        using color = Raychel::colorImp<TestType>;

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
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color addition", "[RaychelMath]")
const color c{1, 1, 1};

const auto c2 = c + color{0, 1, 5};

REQUIRE(c2.r == 1);
REQUIRE(c2.g == 2);
REQUIRE(c2.b == 6);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color subtraction", "[RaychelMath]")
const color c{128};

const auto res = c - color{64, 128, 5};

REQUIRE(res.r == 64);
REQUIRE(res.g == 0);
REQUIRE(res.b == 123);
RAYCHEL_END_TEST