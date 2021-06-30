#include <catch2/catch.hpp>

#include "Raychel/Core/RaychelMath/Impl/QuaternionImpl.inl"
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

    const Quaternion a{};
    const Quaternion b{12, 7, 19, 4};
    const Quaternion c{vec3{0, 1, 0}, 0.0};
    const Quaternion d{vec3{1, 0, 1}, halfPi<TestType>};

    

RAYCHEL_END_TEST