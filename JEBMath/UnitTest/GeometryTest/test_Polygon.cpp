#include "JEBMath/Geometry/Polygon.hpp"
#include "JEBMath/Geometry/Types.hpp"
// #include <JEB/Iterators/Iterators.hpp>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

static void test_IsPolygon()
{
    Dim2::PointD vertices1[] = {
        Dim2::pointD(-3, 0),
        Dim2::pointD(3, 0),
        Dim2::pointD(0, 4),
        Dim2::pointD(-3, 0)
    };
    JT_ASSERT(Polygon::isPolygon(std::begin(vertices1), std::end(vertices1)));

    Dim2::PointD vertices2[] = {
        Dim2::pointD(-3, 0),
        Dim2::pointD(0, 4),
        Dim2::pointD(-3, 0)
    };
    JT_ASSERT(!Polygon::isPolygon(std::begin(vertices2), std::end(vertices2)));

    Dim2::PointD vertices3[] = {
        Dim2::pointD(-3, 0),
        Dim2::pointD(3, 0),
        Dim2::pointD(0, 4),
        Dim2::pointD(-3, 4),
    };
    JT_ASSERT(!Polygon::isPolygon(std::begin(vertices3), std::end(vertices3)));
}

static void test_IsInside()
{
    Dim2::PointD vertices[] = {
        Dim2::pointD(-3, 0),
        Dim2::pointD(3, 0),
        Dim2::pointD(0, 4),
        Dim2::pointD(-3, 0)
    };
    Dim2::PolygonD poly(std::begin(vertices), std::end(vertices));
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 2)),
             Polygon::PolygonPosition::Inside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(-1, 3)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(1, 3)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(-1, 8.0 / 3.0)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 4)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 0)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(-4, 0)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(4, 0)),
             Polygon::PolygonPosition::Outside);
}

static void test_IsInsideConcave()
{
    Dim2::PointD vertices[] = {
        Dim2::pointD(-3, 0),
        Dim2::pointD(-1, 0),
        Dim2::pointD(-1, 1),
        Dim2::pointD(1, 1),
        Dim2::pointD(1, 0),
        Dim2::pointD(3, 0),
        Dim2::pointD(0, 3),
        Dim2::pointD(-3, 0)
    };
    Dim2::PolygonD poly(std::begin(vertices), std::end(vertices));
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 2)),
             Polygon::PolygonPosition::Inside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 1)),
             Polygon::PolygonPosition::OnBorder);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 0.5)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(0, 0)),
             Polygon::PolygonPosition::Outside);
    JT_EQUAL(Polygon::isInside(poly, Dim2::pointD(1.5, 1)),
             Polygon::PolygonPosition::Inside);
}

static void test_IsConvex()
{
    Dim2::PointD convex[] = {
        Dim2::pointD(-2, -1),
        Dim2::pointD(2, -1),
        Dim2::pointD(2, 1),
        Dim2::pointD(-2, 1),
        Dim2::pointD(-2, -1)
    };
    Dim2::PolygonD convexPoly(std::begin(convex), std::end(convex));
    JT_ASSERT(Polygon::isConvex(convexPoly));

    Dim2::PointD concave[] = {
        Dim2::pointD(-2, -1),
        Dim2::pointD(0, 0),
        Dim2::pointD(2, -1),
        Dim2::pointD(0, 2),
        Dim2::pointD(-2, -1)
    };
    Dim2::PolygonD concavePoly(std::begin(concave), std::end(concave));
    JT_ASSERT(!Polygon::isConvex(concavePoly));
}

static void test_IsSelfIntersecting()
{
    Dim2::PointD tri[] = {
        Dim2::pointD(-2, -2),
        Dim2::pointD(2, -2),
        Dim2::pointD(0, 0),
        Dim2::pointD(-2, -2)
    };
    JT_ASSERT(!Polygon::isSelfIntersecting(std::begin(tri),
                                           std::end(tri)));

    Dim2::PointD rect[] = {
        Dim2::pointD(-2, -2),
        Dim2::pointD(2, -2),
        Dim2::pointD(2, 2),
        Dim2::pointD(-2, 2),
        Dim2::pointD(-2, -2)
    };
    JT_ASSERT(!Polygon::isSelfIntersecting(std::begin(rect),
                                           std::end(rect)));
    std::swap(rect[2], rect[3]);
    JT_ASSERT(Polygon::isSelfIntersecting(std::begin(rect),
                                          std::end(rect)));
}

static void test_Rotation()
{
    Dim2::PointD p0 = Dim2::pointD(1.1, 1.1);
    Dim2::PointD p1 = Dim2::pointD(3.3, 3.3);
    Dim2::PointD p2 = Dim2::pointD(6.6, 6.6);
    Dim2::PointD p3 = Dim2::pointD(3.3, 5.7);
    Dim2::PointD p4 = Dim2::pointD(3.3, 1.7);

    double tol = 1e-9;
    JT_EQUAL(Polygon::direction(p0, p1, p2, tol), Polygon::Ahead);
    JT_EQUAL(Polygon::direction(p1, p2, p0, tol), Polygon::Behind);
    JT_EQUAL(Polygon::direction(p2, p2, p1, tol), Polygon::Undetermined);
    JT_EQUAL(Polygon::direction(p0, p1, p3, tol), Polygon::Left);
    JT_EQUAL(Polygon::direction(p0, p1, p4, tol), Polygon::Right);
}

static void test_Angle()
{
    Dim2::PointD p0 = Dim2::pointD(0, 0);
    Dim2::PointD p1 = Dim2::pointD(1, 0);
    Dim2::PointD p2 = Dim2::pointD(1, 1);

    JT_EQUIVALENT(Polygon::angle(p0, p1, p2), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::angle(p2, p1, p0), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::angleCCW(p0, p1, p2), Pi / 2, 1e-9);
    JT_EQUIVALENT(Polygon::angleCCW(p2, p1, p0), 3 * Pi / 2, 1e-9);

    JT_EQUIVALENT(Polygon::angle(p0, p2, p1), Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::angle(p1, p2, p0), Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::angleCCW(p0, p2, p1), 7 * Pi / 4, 1e-9);
    JT_EQUIVALENT(Polygon::angleCCW(p1, p2, p0), Pi / 4, 1e-9);
}

static void test_Area()
{
    Dim2::PointD points[] = {
        Dim2::pointD(-4, 2),
        Dim2::pointD(-1, 8),
        Dim2::pointD(-1, 2),
        Dim2::pointD(-4, 2),
    };
    JT_EQUIVALENT(Polygon::area(std::begin(points), std::end(points)),
                   -9, 1e-9);
}

template <typename PointIt1, typename PointIt2>
static void testOverlap(PointIt1 beg, PointIt1 end, double offset,
                        PointIt2 cmpBeg, PointIt1 cmpEnd, double cmpOffset,
                        PointIt1 exp, double expOffset,
                        PointIt2 expCmp, double expCmpOffset)
{
    auto m = Polygon::overlap(beg, end, offset, cmpBeg, cmpEnd, cmpOffset, 1e-9);
    JT_ASSERT(m.first.first == exp);
    JT_EQUAL(m.first.second, expOffset);
    JT_ASSERT(m.second.first == expCmp);
    JT_EQUAL(m.second.second, expCmpOffset);
}

static void test_Overlap()
{
    using namespace Dim2;
    testOverlap<PointD*, PointD*>(NULL, NULL, 0.5,
                                  NULL, NULL, 0.25,
                                  NULL, 0.5,
                                  NULL, 0.25);
    PointD p1[] = {pointD(-2, -1)};
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  NULL, NULL, 0.25,
                                  std::begin(p1), 0.5,
                                  NULL, 0.25);
    testOverlap<PointD*, PointD*>(NULL, NULL, 0.25,
                                  std::begin(p1), std::end(p1), 0.5,
                                  NULL, 0.25,
                                  std::begin(p1), 0.5);
    PointD p2[] = {pointD(-2, -1)};
    PointD p3[] = {pointD(-2, -2)};
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  std::begin(p2), std::end(p2), 0.5,
                                  std::begin(p1), 0.5,
                                  std::begin(p2), 0.5);
    testOverlap<PointD*, PointD*>(std::begin(p1), std::end(p1), 0.5,
                                  std::begin(p3), std::end(p3), 0.5,
                                  std::begin(p1), 0.5,
                                  std::begin(p3), 0.5);
    PointD p4[] = {pointD(0, 0), pointD(2, 0)};
    PointD p5[] = {pointD(0, 0), pointD(1, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p4), std::end(p4), 0,
                                  std::begin(p5), std::end(p5), 0,
                                  &p4[1], 0,
                                  &p5[2], 0);
    PointD p6[] = {pointD(0.5, 0), pointD(1.5, 0), pointD(2.5, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0.5,
                                  std::begin(p6), std::end(p6), 0,
                                  &p5[2], 0,
                                  &p6[1], 0.5);
    PointD p7[] = {pointD(0, 0), pointD(1, 0), pointD(1, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0,
                                  std::begin(p7), std::end(p7), 0,
                                  &p5[2], 0,
                                  &p7[3], 0);
    PointD p8[] = {pointD(0, 0), pointD(1, 0), pointD(0.9, 0), pointD(2, 0)};
    testOverlap<PointD*, PointD*>(std::begin(p5), std::end(p5), 0,
                                  std::begin(p8), std::end(p8), 0,
                                  &p5[1], 0,
                                  &p8[1], 0);
}

static void test_AreEquivalent()
{
    using namespace Dim2;
    PointD poly1[] = {
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 6, 0),
        pointD( 0, 0),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 0, 0)
    };
    PointD poly2[] = {
        pointD( 0, 0),
        pointD( 4.5, 6),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 6, 0),
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 0, 0)
    };
    JT_ASSERT(Polygon::equivalent(std::begin(poly1), std::end(poly1),
                                  std::begin(poly2), std::end(poly2),
                                  1e-9));
    PointD poly3[] = {
        pointD( 0, 0),
        pointD( 1.5, 2),
        pointD( 3, 0),
        pointD( 0, 0),
        pointD( 0, 0),
        pointD( 6, 8),
        pointD(12, 0),
        pointD( 0, 0),
        pointD( 3, 4),
        pointD( 6, 0),
        pointD( 0, 0)
    };
    JT_ASSERT(!Polygon::equivalent(std::begin(poly1), std::end(poly1),
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
