#include "JEBMath/Geometry/RotatedRect.hpp"
#include "JEBMath/Math/Constants.hpp"
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace JEBMath;
using namespace JEBMath::Dim2;

void test_center()
{
    auto rect = RotatedRect{point2(0, 0), vector2(40, 30), 0};
    JT_EQUAL(rect.center(), point2(20, 15));
    rect.setCenter(point2(0, 0));
    JT_EQUAL(rect.center(), point2(0, 0));
    JT_EQUAL(rect.point(0), point2(-20, -15));
    rect.setAngle(0.9272952180016122);
    JT_ASSERT(equivalent(rect.center(), point2(-20, 10)));

    rect = RotatedRect{point2(0, 0), vector2(40, 30), 0.9272952180016122};
    rect.setCenter(point2(0, 0));
    JT_ASSERT(equivalent(rect.origin(), point2(0, -25)));
}

void test_rotate()
{
    auto rect = RotatedRect{point2(10, 10), vector2(20, 20), 0};
    JT_EQUAL(rect.center(), point2(20, 20));
    rect.rotateCenter(Pi / 4);
    auto delta = std::sqrt(200);
    JT_ASSERT(equivalent(rect.point(0), point2(20.0, 20 - delta)));
    JT_ASSERT(equivalent(rect.point(1), point2(20 + delta, 20.0)));
    JT_ASSERT(equivalent(rect.point(2), point2(20.0, 20 + delta)));
    JT_ASSERT(equivalent(rect.point(3), point2(20 - delta, 20.0)));
}

void test_boundingBox()
{
    auto rect = RotatedRect{point2(0, 0), vector2(20, 20), Pi / 4};
    rect.setCenter(point2(0, 0));
    auto bb = boundingBox(rect);
    auto expected = std::sqrt(200);
    JT_ASSERT(equivalent(bb.first, point2(-expected, -expected)));
    JT_ASSERT(equivalent(bb.second, point2(expected, expected)));
}

void test_point_vs_points()
{
    auto rect = RotatedRect{point2(10, 10), vector2(20, 20), 0.5};
    auto points = rect.points();
    JT_EQUAL(points.size(), 4);
    JT_ASSERT(equivalent(points[0], rect.point(0)));
    JT_ASSERT(equivalent(points[1], rect.point(1)));
    JT_ASSERT(equivalent(points[2], rect.point(2)));
    JT_ASSERT(equivalent(points[3], rect.point(3)));
}

}

JT_SUBTEST("Geometry",
           test_center,
           test_boundingBox,
           test_rotate,
           test_point_vs_points);
