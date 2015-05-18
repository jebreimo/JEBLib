#include "JEBMath/Geometry/Polygon.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_IsPolygon()
{
    Vector<double, 2> vertices1[] = {
        vector2<double>(-3, 0),
        vector2<double>(3, 0),
        vector2<double>(0, 4),
        vector2<double>(-3, 0)
    };
    JT_ASSERT(Polygon::isPolygon(std::begin(vertices1), std::end(vertices1)));

    Vector<double, 2> vertices2[] = {
        vector2<double>(-3, 0),
        vector2<double>(0, 4),
        vector2<double>(-3, 0)
    };
    JT_ASSERT(!Polygon::isPolygon(std::begin(vertices2), std::end(vertices2)));

    Vector<double, 2> vertices3[] = {
        vector2<double>(-3, 0),
        vector2<double>(3, 0),
        vector2<double>(0, 4),
        vector2<double>(-3, 4),
    };
    JT_ASSERT(!Polygon::isPolygon(std::begin(vertices3), std::end(vertices3)));
}

static void test_IsInside()
{
    std::vector<Vector<double, 2>> poly{
        vector2<double>(-3, 0),
        vector2<double>(3, 0),
        vector2<double>(0, 4),
        vector2<double>(-3, 0)
    };
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 2)),
             Polygon::PolygonPosition::Inside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(-1, 3)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(1, 3)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(-1, 8.0 / 3.0)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 4)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 0)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(-4, 0)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(4, 0)),
             Polygon::PolygonPosition::Outside);
}

static void test_IsInsideConcave()
{
    std::vector<Vector<double, 2>> poly{
        vector2<double>(-3, 0),
        vector2<double>(-1, 0),
        vector2<double>(-1, 1),
        vector2<double>(1, 1),
        vector2<double>(1, 0),
        vector2<double>(3, 0),
        vector2<double>(0, 3),
        vector2<double>(-3, 0)
    };
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 2)),
             Polygon::PolygonPosition::Inside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 1)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 0.5)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(0, 0)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, vector2<double>(1.5, 1)),
             Polygon::PolygonPosition::Inside);
}

static void test_IsConvex()
{
    std::vector<Vector<double, 2>> convexPoly{
        vector2<double>(-2, -1),
        vector2<double>(2, -1),
        vector2<double>(2, 1),
        vector2<double>(-2, 1),
        vector2<double>(-2, -1)
    };
    JT_ASSERT(Polygon::isConvex(convexPoly));

    std::vector<Vector<double, 2>> concavePoly{
        vector2<double>(-2, -1),
        vector2<double>(0, 0),
        vector2<double>(2, -1),
        vector2<double>(0, 2),
        vector2<double>(-2, -1)
    };
    JT_ASSERT(!Polygon::isConvex(concavePoly));
}

static void test_IsSelfIntersecting()
{
    Vector<double, 2> tri[] = {
        vector2<double>(-2, -2),
        vector2<double>(2, -2),
        vector2<double>(0, 0),
        vector2<double>(-2, -2)
    };
    JT_ASSERT(!Polygon::isSelfIntersecting(std::begin(tri),
                                           std::end(tri)));

    Vector<double, 2> rect[] = {
        vector2<double>(-2, -2),
        vector2<double>(2, -2),
        vector2<double>(2, 2),
        vector2<double>(-2, 2),
        vector2<double>(-2, -2)
    };
    JT_ASSERT(!Polygon::isSelfIntersecting(std::begin(rect),
                                           std::end(rect)));
    std::swap(rect[2], rect[3]);
    JT_ASSERT(Polygon::isSelfIntersecting(std::begin(rect),
                                          std::end(rect)));
}

static void test_Rotation()
{
    Vector<double, 2> p0 = vector2<double>(1.1, 1.1);
    Vector<double, 2> p1 = vector2<double>(3.3, 3.3);
    Vector<double, 2> p2 = vector2<double>(6.6, 6.6);
    Vector<double, 2> p3 = vector2<double>(3.3, 5.7);
    Vector<double, 2> p4 = vector2<double>(3.3, 1.7);

    double tol = 1e-9;
    JT_EQUAL(Polygon::getDirection(p0, p1, p2, tol), Polygon::Ahead);
    JT_EQUAL(Polygon::getDirection(p1, p2, p0, tol), Polygon::Behind);
    JT_EQUAL(Polygon::getDirection(p2, p2, p1, tol), Polygon::Undetermined);
    JT_EQUAL(Polygon::getDirection(p0, p1, p3, tol), Polygon::Left);
    JT_EQUAL(Polygon::getDirection(p0, p1, p4, tol), Polygon::Right);
}

static void test_Angle()
{
    Vector<double, 2> p0 = vector2<double>(0, 0);
    Vector<double, 2> p1 = vector2<double>(1, 0);
    Vector<double, 2> p2 = vector2<double>(1, 1);

    JT_EQUIVALENT(Polygon::getAngle(p0, p1, p2), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::getAngle(p2, p1, p0), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::getAngleCCW(p0, p1, p2), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::getAngleCCW(p2, p1, p0), 3 * Pi / 2, 1e-9);

    JT_EQUIVALENT(Polygon::getAngle(p0, p2, p1), Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::getAngle(p1, p2, p0), Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::getAngleCCW(p0, p2, p1), 7 * Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::getAngleCCW(p1, p2, p0), Pi / 4, 1e-9);
}

static void test_Area()
{
    Vector<double, 2> points[] = {
        vector2<double>(-4, 2),
        vector2<double>(-1, 8),
        vector2<double>(-1, 2),
        vector2<double>(-4, 2),
    };
    JT_EQUIVALENT(Polygon::getArea(std::begin(points), std::end(points)),
                   -9, 1e-9);
}

static void testOverlap(Vector<double, 2>* beg, Vector<double, 2>* end,
                        double offset,
                        Vector<double, 2>* cmpBeg, Vector<double, 2>* cmpEnd,
                        double cmpOffset,
                        Vector<double, 2>* exp, double expOffset,
                        Vector<double, 2>* expCmp, double expCmpOffset)
{
    auto m = Polygon::overlap(beg, end, offset,
                              cmpBeg, cmpEnd, cmpOffset, 1e-9);
    JT_ASSERT(m.first.first == exp);
    JT_EQUAL(m.first.second, expOffset);
    JT_ASSERT(m.second.first == expCmp);
    JT_EQUAL(m.second.second, expCmpOffset);
}

static void test_Overlap()
{
    testOverlap(NULL, NULL, 0.5,
                NULL, NULL, 0.25,
                NULL, 0.5,
                NULL, 0.25);
    Vector<double, 2> p1[] = {vector2(-2, -1)};
    testOverlap(std::begin(p1), std::end(p1), 0.5,
                NULL, NULL, 0.25,
                std::begin(p1), 0.5,
                NULL, 0.25);
    testOverlap(NULL, NULL, 0.25,
                std::begin(p1), std::end(p1), 0.5,
                NULL, 0.25,
                std::begin(p1), 0.5);
    Vector<double, 2> p2[] = {vector2(-2, -1)};
    Vector<double, 2> p3[] = {vector2(-2, -2)};
    testOverlap(std::begin(p1), std::end(p1), 0.5,
                std::begin(p2), std::end(p2), 0.5,
                std::begin(p1), 0.5,
                std::begin(p2), 0.5);
    testOverlap(std::begin(p1), std::end(p1), 0.5,
                std::begin(p3), std::end(p3), 0.5,
                std::begin(p1), 0.5,
                std::begin(p3), 0.5);
    Vector<double, 2> p4[] = {vector2(0, 0), vector2(2, 0)};
    Vector<double, 2> p5[] = {vector2(0, 0), vector2(1, 0), vector2(2, 0)};
    testOverlap(std::begin(p4), std::end(p4), 0,
                std::begin(p5), std::end(p5), 0,
                &p4[1], 0,
                &p5[2], 0);
    Vector<double, 2> p6[] = {vector2(0.5, 0.0), vector2(1.5, 0.0), vector2(2.5, 0.0)};
    testOverlap(std::begin(p5), std::end(p5), 0.5,
                std::begin(p6), std::end(p6), 0,
                &p5[2], 0,
                &p6[1], 0.5);
    Vector<double, 2> p7[] = {vector2(0, 0), vector2(1, 0), vector2(1, 0), vector2(2, 0)};
    testOverlap(std::begin(p5), std::end(p5), 0,
                std::begin(p7), std::end(p7), 0,
                &p5[2], 0,
                &p7[3], 0);
    Vector<double, 2> p8[] = {vector2(0, 0), vector2(1, 0), vector2(0.9, 0.0), vector2(2, 0)};
    testOverlap(std::begin(p5), std::end(p5), 0,
                std::begin(p8), std::end(p8), 0,
                &p5[1], 0,
                &p8[1], 0);
}

static void test_AreEquivalent()
{
    Vector<double, 2> poly1[] = {
        vector2( 0, 0),
        vector2( 3, 4),
        vector2( 6, 0),
        vector2( 6, 0),
        vector2( 0, 0),
        vector2( 6, 8),
        vector2(12, 0),
        vector2( 0, 0)
    };
    Vector<double, 2> poly2[] = {
        vector2( 0, 0),
        vector2( 4.5, 6.0),
        vector2( 6, 8),
        vector2(12, 0),
        vector2( 6, 0),
        vector2( 0, 0),
        vector2( 3, 4),
        vector2( 6, 0),
        vector2( 0, 0)
    };
    JT_ASSERT(Polygon::areEquivalent(std::begin(poly1), std::end(poly1),
                                     std::begin(poly2), std::end(poly2),
                                     1e-9));
    Vector<double, 2> poly3[] = {
        vector2( 0, 0),
        vector2( 1.5, 2.0),
        vector2( 3, 0),
        vector2( 0, 0),
        vector2( 0, 0),
        vector2( 6, 8),
        vector2(12, 0),
        vector2( 0, 0),
        vector2( 3, 4),
        vector2( 6, 0),
        vector2( 0, 0)
    };
    JT_ASSERT(!Polygon::areEquivalent(std::begin(poly1), std::end(poly1),
                                      std::begin(poly3), std::end(poly3),
                                      1e-9));
}

JT_SUBTEST("Geometry",
           test_IsPolygon,
           test_IsInside,
           test_IsInsideConcave,
           test_IsSelfIntersecting,
           test_IsConvex,
           test_Rotation,
           test_Angle,
           test_Area,
           test_Overlap,
           test_AreEquivalent);
