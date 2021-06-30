#include <catch2/catch.hpp>
#include <type_traits>

#include "Raychel/Core/RaychelMath/Impl/vec3Impl.inl"
#include "Raychel/Core/RaychelMath/vec3.h"

//clang-format doesn't like these macros
// clang-format off

#ifdef _MSC_VER
    #pragma warning( push )
    #pragma warning (disable : 4244 4305) //MSVC's warnings about narrowing conversion are nice to have, but not this time
#endif

#define RAYCHEL_VEC3_TEST_TYPES int, size_t, float, double, long double
#define RAYCHEL_VEC3_FLOATING_TYPES float, double, long double

#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_VEC3_TEST_TYPES)           \
    {                                                                          \
        using namespace Raychel;                                               \
        using vec3 = vec3Imp<TestType>;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating vectors", "[RaychelMath][Vector3]")

    const vec3 v{};
    const vec3 v1{12};
    const vec3 v2{5, 200};
    const vec3 v3{5, 100, 12};

    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);

    REQUIRE(v1.x == 12);
    REQUIRE(v1.y == 0);
    REQUIRE(v1.z == 0);

    REQUIRE(v2.x == 5);
    REQUIRE(v2.y == 200);
    REQUIRE(v2.z == 0);

    REQUIRE(v3.x == 5);
    REQUIRE(v3.y == 100);
    REQUIRE(v3.z == 12);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector addition", "[RaychelMath][Vector3]")

    vec3 v{12, 13, 4};

    const vec3 res = v + vec3{1, 12, 9};

    REQUIRE(res.x == 13);
    REQUIRE(res.y == 25);
    REQUIRE(res.z == 13);

    v += vec3{1, 7, 12};

    REQUIRE(v.x == 13);
    REQUIRE(v.y == 20);
    REQUIRE(v.z == 16);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector subtraction", "[RaychelMath][Vector3]")

    vec3 v{7, 500, 9};

    const vec3 res = v - vec3{7, 12, 8};

    REQUIRE(res.x == 0);
    REQUIRE(res.y == 488);
    REQUIRE(res.z == 1);


    v -= res;

    REQUIRE(v.x == 7);
    REQUIRE(v.y == 12);
    REQUIRE(v.z == 8);

    if constexpr (std::is_signed_v<TestType>) {

        const vec3 v2 = -v;

        REQUIRE(v2.x == -7);
        REQUIRE(v2.y == -12);
        REQUIRE(v2.z == -8);

    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector Multiplication", "[RaychelMath][Vector3]")

    const vec3 v{1, 12, 5};
    const vec3 v1{0, 4, 7};

    vec3 res = v * v1;

    REQUIRE(res.x == 0);
    REQUIRE(res.y == 48);
    REQUIRE(res.z == 35);

    res = v * TestType(2);

    REQUIRE(res.x == 2);
    REQUIRE(res.y == 24);
    REQUIRE(res.z == 10);



    vec3 v2{0, 5, 7};

    v2 *= vec3{12, 4, 1};

    REQUIRE(v2.x == 0);
    REQUIRE(v2.y == 20);
    REQUIRE(v2.z == 7);

    v2 = vec3{0, 5, 7};

    v2 *= 5;

    REQUIRE(v2.x == 0);
    REQUIRE(v2.y == 25);
    REQUIRE(v2.z == 35);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector Division", "[RaychelMath][Vector3]")

    const vec3 v{3, 12, 63};
    const vec3 v1{1, 4, 7};

    vec3 res = v / v1;

    REQUIRE(res.x == 3);
    REQUIRE(res.y == 3);
    REQUIRE(res.z == 9);

    res = v / TestType(3);

    REQUIRE(res.x == 1);
    REQUIRE(res.y == 4);
    REQUIRE(res.z == 21);



    vec3 v2{3, 12, 63};

    v2 /= vec3{1, 3, 7};

    REQUIRE(v2.x == 3);
    REQUIRE(v2.y == 4);
    REQUIRE(v2.z == 9);

    v2 = vec3{3, 12, 63};

    v2 /= 3;

    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 4);
    REQUIRE(v2.z == 21);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector modulo", "[RaychelMath][Vector3]")

    const vec3 v{1, 12, 8};
    const vec3 m{9, 3, 12};

    vec3 res = v % m;

    REQUIRE(res.x == 1);
    REQUIRE(res.y == 0);
    REQUIRE(res.z == 8);

    res = v % TestType(3);

    REQUIRE(res.x == 1);
    REQUIRE(res.y == 0);
    REQUIRE(res.z == 2);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector comparison: equality", "[RaychelMath][Vector3]")

    const vec3 v{12, 7, 9};
    const vec3 v2{};

    REQUIRE(v == v);
    REQUIRE(v == vec3{12, 7, 9});
    REQUIRE(v != vec3{12, 0, 4 });

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector comparison: greater than", "[RaychelMath][Vector3]")

    const vec3 v{1, 7, 12};
    const vec3 comp{12, 7, 9};

    const auto gt = v > comp;

    REQUIRE(gt.x == false);
    REQUIRE(gt.y == false);
    REQUIRE(gt.z == true);

    const auto gt_e = v >= comp;

    REQUIRE(gt_e.x == false);
    REQUIRE(gt_e.y == true);
    REQUIRE(gt_e.z == true);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector comparison: less than", "[RaychelMath][Vector3]")

    const vec3 v{1, 7, 12};
    const vec3 comp{12, 7, 9};

    const auto lt = v < comp;

    REQUIRE(lt.x == true);
    REQUIRE(lt.y == false);
    REQUIRE(lt.z == false);

    const auto lt_e = v <= comp;

    REQUIRE(lt_e.x == true);
    REQUIRE(lt_e.y == true);
    REQUIRE(lt_e.z == false);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector dot product", "[RaychelMath][Vector3]")

    const vec3 a{0, 1, 0};
    
    //v * v == |v|²
    {
        const vec3 b{0, 1, 0};
        const auto d = dot(a, b);

        REQUIRE(d == 1);
    }

    //a * b == 0 => a and b are orthogonal
    {
        const vec3 b{1, 0, 0};
        const auto d = dot(a, b);

        REQUIRE(d == 0);
    }

    //a * b == -1 * |a| * |b| => a and b point in different directions
    if constexpr(!std::is_unsigned<TestType>::value)
    {
        const vec3 b{0, -1, 0};
        const auto d = dot(a, b);

        REQUIRE(d == -1);
    }

    //a * b = cos(theta)        
    if constexpr(std::is_floating_point_v<TestType>) //NOLINT: clang-tidy really does not like macros
    {
        const vec3 b = vec3(std::sqrt(2.0), std::sqrt(2.0), 0);

        const auto d = dot(a, b);

        REQUIRE(equivalent<TestType>(d, std::sqrt(2.0)));
    }

    //v * 0 = 0
    REQUIRE(dot(vec3{}, vec3{12, 400, 7}) == 0);

    //v * v = |v|²
    const vec3 v{12, 45, 9};
    REQUIRE(dot(v, v) == 2'250);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector magnitude", "[RaychelMath][Vector3]")

    //the zero vector has magnitude 0
    REQUIRE(mag(vec3{}) == 0);

    //the orthonormal basis vectors have magnitude 1
    REQUIRE(mag(vec3{1, 0, 0}) == 1);
    REQUIRE(mag(vec3{0, 1, 0}) == 1);
    REQUIRE(mag(vec3{0, 0, 1}) == 1);

    //Pythagoras holds
    REQUIRE(mag(vec3{1, 2, 2}) == 3);
    REQUIRE(mag(vec3{12, 15, 16}) == 25);

    if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(mag(vec3{1, 0, 1}) == std::sqrt(TestType(2.0)));
        
        const vec3 v{std::sqrt(TestType(2)), 0, std::sqrt(TestType(2))};
        const auto m = mag(v);
        REQUIRE(equivalent<TestType>(m, 2));
    }


    REQUIRE(magSq(vec3{}) == 0);

    REQUIRE(magSq(vec3{1, 0, 0}) == 1);
    REQUIRE(magSq(vec3{0, 1, 0}) == 1);
    REQUIRE(magSq(vec3{0, 0, 1}) == 1);

    REQUIRE(magSq(vec3{4, 17, 12}) == 449);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector normalization", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const TestType inv_sqrt_2 = 1.0 / std::sqrt(2.0);

    {
        const vec3 v = normalize(vec3{1, 0, 1});

        REQUIRE(equivalent<TestType>(v.x, inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v.y, 0));
        REQUIRE(equivalent<TestType>(v.z, inv_sqrt_2));
    }

    {
        const vec3 v = normalize(vec3{12, 0, 12});

        REQUIRE(equivalent(v.x, inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v.y, 0));
        REQUIRE(equivalent(v.z, inv_sqrt_2));
    }

}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector absolute value", "[RaychelMath][Vector3]")

    //abs does not make sense for unsigned types
    if constexpr(std::is_signed_v<TestType>) {
        vec3 v{-12, 0, 9};

        vec3 res = abs(v);

        REQUIRE(res.x == 12);
        REQUIRE(res.y == 0);
        REQUIRE(res.z == 9);

        v = -v;

        res = abs(v);

        REQUIRE(res.x == 12);
        REQUIRE(res.y == 0);
        REQUIRE(res.z == 9);
    }


RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector max/min", "[RaychelMath][Vector3]")

    const vec3 a{0, 2, 15};
    const vec3 b{0, 300, 4};

    vec3 res = max(a, b);

    REQUIRE(res.x == 0);
    REQUIRE(res.y == 300);
    REQUIRE(res.z == 15);

    
    
    res = min(a, b);

    REQUIRE(res.x == 0);
    REQUIRE(res.y == 2);
    REQUIRE(res.z == 4);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector sin/cos", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{0, halfPi<TestType>, -1};

    const vec3 res_sin = sin(v);

    REQUIRE(equivalent<TestType>(res_sin.x, 0));
    REQUIRE(equivalent<TestType>(res_sin.y, 1));
    REQUIRE(equivalent<TestType>(res_sin.z, std::sin(-1.0)));


    const vec3 res_cos = cos(v);

    REQUIRE(res_cos.x == 1);
    REQUIRE(equivalent(res_cos.y, std::cos(halfPi<TestType>)));
    REQUIRE(equivalent<TestType>(res_cos.z, std::cos(-1.0)));

}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector distance", "[RaychelMath][Vector3]")

    const vec3 a{12, 4, 7};

    {
        const vec3 b{};

        const auto d = dist(a, b);

        REQUIRE(d == mag(a));
    }

    {
        const vec3 b{10, 1, 1};

        const auto d = dist(a, b);

        REQUIRE(d == 7);
    }

    if constexpr (std::is_signed_v<TestType>)
    {
        const vec3 b{0, -12, 28};

        const auto d = dist(a, b);

        REQUIRE(d == 29);
    }

    //NOLINTNEXTLINE: clang-tidy gets really confused by these ifs
    if constexpr(std::is_floating_point_v<TestType>)
    {
        const vec3 b{27, 4, 9};

        const auto d = dist(a, b);

        REQUIRE(equivalent<TestType>(d, std::sqrt(TestType(229))));
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector squared distance", "[RaychelMath][Vector3]")

    const vec3 a{12, 4, 7};

    {
        const vec3 b{};

        const auto d = distSq(a, b);

        REQUIRE(d == magSq(a));
    }

    {
        const vec3 b{10, 1, 1};

        const auto d = distSq(a, b);

        REQUIRE(d == 49);
    }

    if constexpr (std::is_signed_v<TestType>)
    {
        const vec3 b{0, -12, 28};

        const auto d = distSq(a, b);

        REQUIRE(d == 841);
    }

    //NOLINTNEXTLINE: clang-tidy doesn't like this file :(
    {
        const vec3 b{27, 4, 9};

        const auto d = distSq(a, b);

        REQUIRE(d == 229);
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector cross product", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    //v x 0 = 0 for any v
    {
        const vec3 v{12, -4, 7};
        const vec3 b{};

        const vec3 c = cross(v, b);

        REQUIRE(equivalent<TestType>(c.x, 0));
        REQUIRE(equivalent<TestType>(c.y, 0));
        REQUIRE(equivalent<TestType>(c.z, 0));
    }

    //a || b => a x b = 0
    {
        const vec3 v{9, 123, 6};

        vec3 c = cross(v, v);

        REQUIRE(equivalent<TestType>(c.x, 0));
        REQUIRE(equivalent<TestType>(c.y, 0));
        REQUIRE(equivalent<TestType>(c.z, 0));

        c = cross(v, -v);

        REQUIRE(equivalent<TestType>(c.x, 0));
        REQUIRE(equivalent<TestType>(c.y, 0));
        REQUIRE(equivalent<TestType>(c.z, 0));

        c = cross(v, v * TestType(3));

        REQUIRE(equivalent<TestType>(c.x, 0));
        REQUIRE(equivalent<TestType>(c.y, 0));
        REQUIRE(equivalent<TestType>(c.z, 0));
    }

    //a x b = -(b x a)
    {
        const vec3 a{-1, 12, 0};
        const vec3 b{1, 0, 2};

        const vec3 c_pos = cross(a, b);
        const vec3 c_neg = cross(b, a);

        REQUIRE(equivalent<TestType>(c_pos.x, -c_neg.x));
        REQUIRE(equivalent<TestType>(c_pos.y, -c_neg.y));
        REQUIRE(equivalent<TestType>(c_pos.z, -c_neg.z));
    }

    //cross product follows the right hand rule
    {
        constexpr vec3 x{1, 0, 0};
        constexpr vec3 y{0, 1, 0};
        constexpr vec3 z{0, 0, 1};

        const vec3 xy = cross(x, y);

        REQUIRE(equivalent<TestType>(xy.x, 0));
        REQUIRE(equivalent<TestType>(xy.y, 0));
        REQUIRE(equivalent<TestType>(xy.z, 1));

        const vec3 xz = cross(x, z);

        REQUIRE(equivalent<TestType>(xz.x, 0));
        REQUIRE(equivalent<TestType>(xz.y, 1));
        REQUIRE(equivalent<TestType>(xz.z, 0));

        const vec3 zy = cross(z, y);

        REQUIRE(equivalent<TestType>(zy.x, 1));
        REQUIRE(equivalent<TestType>(zy.y, 0));
        REQUIRE(equivalent<TestType>(zy.z, 0));
    }
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: x", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{4, 1, 0};
    const vec3 v2{4, 1, 2};

    vec3 r = rotateX(v, pi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 4));
    REQUIRE(equivalent<TestType>(r.y, -1));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateX(v2, halfPi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 4));
    REQUIRE(equivalent<TestType>(r.y, -2));
    REQUIRE(equivalent<TestType>(r.z, 1));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateX(v3, theta);
    const vec3 r_neg = rotateX(v3, theta - 10*pi<TestType>);

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: y", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotateY(v, pi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, 4));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateY(v2, halfPi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 2));
    REQUIRE(equivalent<TestType>(r.y, 1));
    REQUIRE(equivalent<TestType>(r.z, -4));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateY(v3, theta);
    const vec3 r_neg = rotateY(v3, theta - 10*pi<TestType>);

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: z", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotateZ(v, pi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, -4));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateZ(v2, halfPi<TestType>);

    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, 4));
    REQUIRE(equivalent<TestType>(r.z, 2));

    


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateZ(v3, theta);
    const vec3 r_neg = rotateZ(v3, theta - 10*pi<TestType>);

    

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif