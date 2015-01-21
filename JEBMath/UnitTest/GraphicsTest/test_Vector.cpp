#include "JEBMath/JEBVectorMath.hpp"

#include <cmath>
#include <JEBTest/JEBTest.hpp>
#include "JEBMath/Math/Utilities.hpp"

namespace {

using namespace JEBMath;

void test_Basics2D()
{
    auto u = vector2(2.0, 1.0);
    auto v = vector2(3, 4);
    JT_EQUAL(u[0], 2);
    JT_EQUAL(u[1], 1);
    JT_EQUAL(v[0], 3);
    JT_EQUAL(v[1], 4);
    JT_EQUAL(u * v, vector2(6, 4));
    JT_EQUAL(u + v, vector2(5, 5));
    JT_EQUAL(u - v, vector2(-1, -3));
    JT_EQUAL(u * 3, vector2(6, 3));
    JT_EQUAL(3 * u, vector2(6, 3));
    JT_EQUAL(u / 3, vector2(2.0 / 3, 1.0 / 3));
    JT_EQUAL(6 / u, vector2(3, 6));
    JT_EQUAL(u += v, vector2(5, 5));
    JT_EQUAL(u -= v, vector2(2, 1));
    JT_EQUAL(u *= 3, vector2(6, 3));
    JT_EQUAL(u /= 2, vector2(3.0, 1.5));
    JT_EQUAL(u *= v, vector2(9, 6));
    JT_EQUAL(u *= 2, vector2(18, 12));
    JT_EQUAL(u /= v, vector2(6, 3));
    JT_EQUAL(inner(u, v), 30);
    JT_EQUIVALENT(length(v), 5, 1e-10);
}

void test_Basics4D()
{
    auto u = vector4(2.0, 1.0, 4.0, 3.0);
    auto v = vector4(3, 4, -1, -2);
    JT_EQUAL(u[0], 2);
    JT_EQUAL(u[1], 1);
    JT_EQUAL(u[2], 4);
    JT_EQUAL(u[3], 3);
    JT_EQUAL(v[0], 3);
    JT_EQUAL(v[1], 4);
    JT_EQUAL(v[2], -1);
    JT_EQUAL(v[3], -2);
    JT_EQUAL(u * v, vector4(6, 4, -4, -6));
    JT_EQUAL(u + v, vector4(5, 5, 3, 1));
    JT_EQUAL(u - v, vector4(-1, -3, 5, 5));
    JT_EQUAL(u * 3, vector4(6, 3, 12, 9));
    JT_EQUAL(3 * u, vector4(6, 3, 12, 9));
    JT_EQUAL(u / 3, vector4(2.0 / 3, 1.0 / 3, 4.0 / 3, 1.0));
    JT_EQUAL(12 / u, vector4(6, 12, 3, 4));
    JT_EQUAL(u += v, vector4(5, 5, 3, 1));
    JT_EQUAL(u -= v, vector4(2, 1, 4, 3));
    JT_EQUAL(u *= 3, vector4(6, 3, 12, 9));
    JT_EQUAL(u /= 2, vector4(3.0, 1.5, 6.0, 4.5));
    JT_EQUAL(u *= v, vector4(9, 6, -6, -9));
    JT_EQUAL(u *= 2, vector4(18, 12, -12, -18));
    JT_EQUAL(u /= v, vector4(6, 3, 12, 9));
    JT_EQUAL(inner(u, v), 18 + 12 - 12 - 18);
    JT_EQUIVALENT(length(v), sqrt(9 + 16 + 1 + 4), 1e-10);
}

void test_Cross()
{
    auto u = vector3(1, 2, 3);
    auto v = vector3(0, 1, 2);
    JT_EQUAL(cross(u, v), vector3(1, -2, 1));
}

void test_Rotate()
{
    JT_ASSERT(equivalent(rotate(vector2(100, 0), radians(30)),
                         vector2(50 * std::sqrt(3), 50.0), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(100, 0), radians(45)),
                         vector2(100 / std::sqrt(2), 100 / std::sqrt(2)),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(100, 0), radians(60)),
                         vector2(50.0, 50 * std::sqrt(3)), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), radians(-60)),
                         vector2(50 * std::sqrt(3), 50.0), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), radians(-45)),
                         vector2(100 / std::sqrt(2), 100 / std::sqrt(2)),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), radians(-30)),
                         vector2(50.0, 50 * std::sqrt(3)), 1e-12));

    JT_ASSERT(equivalent(rotate(vector2(1 / std::sqrt(2), 1 / std::sqrt(2)),
                                radians(45)),
                         vector2(0, 1),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(1 / std::sqrt(2), 1 / std::sqrt(2)),
                                radians(135)),
                         vector2(-1, 0),
                         1e-12));
}

void test_Types()
{
    auto u = vector2(1, 2);
    JT_EQUAL(typeid(typename decltype(u)::ValueType).name(),
             typeid(int).name());
    auto v = vector2(2.0, 4.0);
    JT_EQUAL(typeid(typename decltype(v)::ValueType).name(),
             typeid(double).name());
    auto w = u + v;
    JT_EQUAL(typeid(typename decltype(w)::ValueType).name(),
             typeid(double).name());
}

void test_Constructors()
{
    auto u = vector2(1, 2);
    Vector<double, 4> v = u;
    JT_EQUAL(v[0], 1);
    JT_EQUAL(v[1], 2);
    JT_EQUAL(v[2], 0);
    JT_EQUAL(v[3], 0);
}

JT_SUBTEST("Graphics",
           test_Basics2D,
           test_Basics4D,
           test_Cross,
           test_Rotate,
           test_Types,
           test_Constructors);
}
