#include "JEBMath/Geometry/RotatedRect.hpp"
#include "JEBMath/Math/Constants.hpp"
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace JEBMath;

void test_center()
{
    auto rect = RotatedRect{vector2(0, 0), vector2(40, 30), 0};
    JT_EQUAL(rect.getCenter(), vector2(20, 15));
    rect.setCenter(vector2(0.0, 0.0));
    JT_EQUAL(rect.getCenter(), vector2(0, 0));
    JT_EQUAL(rect.getPoint(0), vector2(-20, -15));
    rect.setAngle(0.9272952180016122);
    JT_ASSERT(areEquivalent(rect.getCenter(), vector2(-20, 10)));

    rect = RotatedRect{vector2(0, 0), vector2(40, 30), 0.9272952180016122};
    rect.setCenter(vector2(0.0, 0.0));
    JT_ASSERT(areEquivalent(rect.getOrigin(), vector2(0, -25)));
}

void test_rotate()
{
    auto rect = RotatedRect{vector2(10, 10), vector2(20, 20), 0};
    JT_EQUAL(rect.getCenter(), vector2(20, 20));
    rect.rotateCenter(Pi / 4);
    auto delta = std::sqrt(200);
    JT_ASSERT(areEquivalent(rect.getPoint(0), vector2(20.0, 20 - delta)));
    JT_ASSERT(areEquivalent(rect.getPoint(1), vector2(20 + delta, 20.0)));
    JT_ASSERT(areEquivalent(rect.getPoint(2), vector2(20.0, 20 + delta)));
    JT_ASSERT(areEquivalent(rect.getPoint(3), vector2(20 - delta, 20.0)));
}

void test_boundingBox()
{
    auto rect = RotatedRect{vector2(0, 0), vector2(20, 20), Pi / 4};
    rect.setCenter(vector2(0.0, 0.0));
    auto bb = getBoundingBox(rect);
    auto expected = std::sqrt(200);
    JT_ASSERT(areEquivalent(bb.first, vector2(-expected, -expected)));
    JT_ASSERT(areEquivalent(bb.second, vector2(expected, expected)));
}

void test_point_vs_points()
{
    auto rect = RotatedRect{vector2(10, 10), vector2(20, 20), 0.5};
    auto points = rect.getPoints();
    JT_EQUAL(points.size(), 4);
    JT_ASSERT(areEquivalent(points[0], rect.getPoint(0)));
    JT_ASSERT(areEquivalent(points[1], rect.getPoint(1)));
    JT_ASSERT(areEquivalent(points[2], rect.getPoint(2)));
    JT_ASSERT(areEquivalent(points[3], rect.getPoint(3)));
}

}

JT_SUBTEST("Geometry",
           test_center,
           test_boundingBox,
           test_rotate,
           test_point_vs_points);
