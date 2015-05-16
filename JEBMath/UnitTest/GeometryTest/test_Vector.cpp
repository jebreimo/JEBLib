#include "JEBMath/Geometry/Vector.hpp"

#include <cmath>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

namespace {

void test_Basics()
{
    auto u = vector2<double>(2, 1);
    auto v = vector2<double>(3, 4);
    JT_EQUAL(x(u), 2);
    JT_EQUAL(y(u), 1);
    JT_EQUAL(x(v), 3);
    JT_EQUAL(y(v), 4);
    JT_EQUAL(u * v, 10);
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
    JT_EQUIVALENT(length(v), 5, 1e-10);
}

void test_Point()
{
    auto a = point2<double>(3, 12);
    auto b = point2<double>(8, -11);
    JT_EQUAL(b - a, vector2<double>(5, -23));
}

void test_Rotate()
{
    JT_ASSERT(equivalent(rotate(vector2(100, 0), toRadians(30)),
                         vector2(50 * std::sqrt(3), 50.0), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(100, 0), toRadians(45)),
                         vector2(100 / std::sqrt(2), 100 / std::sqrt(2)),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(100, 0), toRadians(60)),
                         vector2(50.0, 50 * std::sqrt(3)), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), toRadians(-60)),
                         vector2(50 * std::sqrt(3), 50.0), 1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), toRadians(-45)),
                         vector2(100 / std::sqrt(2), 100 / std::sqrt(2)),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(0, 100), toRadians(-30)),
                         vector2(50.0, 50 * std::sqrt(3)), 1e-12));

    JT_ASSERT(equivalent(rotate(vector2(1 / std::sqrt(2), 1 / std::sqrt(2)),
                                toRadians(45)),
                         vector2(0, 1),
                         1e-12));
    JT_ASSERT(equivalent(rotate(vector2(1 / std::sqrt(2), 1 / std::sqrt(2)),
                                toRadians(135)),
                         vector2(-1, 0),
                         1e-12));
}

void test_Scale()
{
    JT_EQUAL(scale(vector2(13.5, 12.5), vector2(10, 20)), vector2(135, 250));
}

JT_SUBTEST("Geometry", test_Basics, test_Point, test_Rotate, test_Scale);

}
