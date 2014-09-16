#include "JEBMath/Geometry/Polygon.hpp"
#include <iterator>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

template <typename It>
static size_t removePolygon(std::vector<std::vector<Dim2::PointD>>& result,
                            It polyBegin, It polyEnd)
{
    size_t i = 0;
    for (auto it = result.begin(); it != result.end(); ++it)
    {
        if (Polygon::equivalent(it->begin(), it->end(), polyBegin, polyEnd, 1e-9))
        {
            result.erase(it);
            return i;
        }
        ++i;
    }
    return ~(size_t)0;
}

#define RECTANGLE2(name, x, y, w, h) \
    Dim2::PointD name[] = { \
        Dim2::pointD(x, y), \
        Dim2::pointD(x + w, y), \
        Dim2::pointD(x + w, y + h), \
        Dim2::pointD(x, y + h), \
        Dim2::pointD(x, y) \
    }

static void test_OverlappingSquareAndRect()
{
    Dim3::PointD points[] = {
        Dim3::pointD(-2, -2, 5),
        Dim3::pointD( 2, -2, 3),
        Dim3::pointD( 2,  3, 5),
        Dim3::pointD(-2,  3, 5),
        Dim3::pointD(-2, -3, 3),
        Dim3::pointD( 2, -3, 3),
        Dim3::pointD( 2,  2, 5),
        Dim3::pointD(-2,  2, 5),
        Dim3::pointD(-2, -2, 5)
    };
    RECTANGLE2(outer, 2, 3, -4, -6);
    RECTANGLE2(inner0, -2, 3, 4, -1);
    RECTANGLE2(inner1, -2, 2, 4, -4);
    RECTANGLE2(inner2, -2, -2, 4, -1);

    std::vector<std::vector<Dim2::PointD>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 4);
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    JT_ASSERT(~removePolygon(result, std::begin(inner0), std::end(inner0)));
    JT_ASSERT(~removePolygon(result, std::begin(inner1), std::end(inner1)));
    JT_ASSERT(~removePolygon(result, std::begin(inner2), std::end(inner2)));
}

static void test_FiveOverlappingSquares()
{
    Dim2::PointD points[] = {
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  0),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2)
    };
    std::vector<std::vector<Dim2::PointD>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 2);
    RECTANGLE2(outer, 2, 2, -4, -4);
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    RECTANGLE2(inner, -2, 2, 4, -4);
    JT_ASSERT(~removePolygon(result, std::begin(inner), std::end(inner)));
}

#define DIAMOND2(name, x, y, w, h) \
    Dim2::PointD name[] = { \
        Dim2::pointD(x, y - h), \
        Dim2::pointD(x + w, y), \
        Dim2::pointD(x, y + h), \
        Dim2::pointD(x - w, y), \
        Dim2::pointD(x, y - h) \
    }

static void test_Ribbon()
{
    //    /\/\
    //    \/\/
    //    /\/\
    //   / /\ \
    //  /  --  \
    //  --------
    Dim2::PointD points[] = {
        Dim2::pointD(-2,  2),
        Dim2::pointD(-1,  3),
        Dim2::pointD( 4, -2),
        Dim2::pointD(-4, -2),
        Dim2::pointD( 1,  3),
        Dim2::pointD( 2,  2),
        Dim2::pointD(-1, -1),
        Dim2::pointD( 1, -1),
        Dim2::pointD(-2,  2),
    };
    std::vector<std::vector<Dim2::PointD>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 6);
    Dim2::PointD outer[] = {
        Dim2::pointD(-4, -2),
        Dim2::pointD( 4, -2),
        Dim2::pointD( 1,  1),
        Dim2::pointD( 2,  2),
        Dim2::pointD( 1,  3),
        Dim2::pointD( 0,  2),
        Dim2::pointD(-1,  3),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-1,  1),
        Dim2::pointD(-4, -2)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    Dim2::PointD inner0[] = {
        Dim2::pointD(-4, -2),
        Dim2::pointD(-1,  1),
        Dim2::pointD( 0,  0),
        Dim2::pointD(-1, -1),
        Dim2::pointD( 1, -1),
        Dim2::pointD( 0,  0),
        Dim2::pointD( 1,  1),
        Dim2::pointD( 4, -2),
        Dim2::pointD(-4, -2)
    };
    JT_ASSERT(~removePolygon(result, std::begin(inner0), std::end(inner0)));
    Dim2::PointD inner1[] = {
        Dim2::pointD(-1, -1),
        Dim2::pointD( 0,  0),
        Dim2::pointD( 1, -1),
        Dim2::pointD(-1, -1)
    };
    JT_ASSERT(~removePolygon(result, std::begin(inner1), std::end(inner1)));
    DIAMOND2(inner2, 0, 1, -1, 1);
    JT_ASSERT(~removePolygon(result, std::begin(inner2), std::end(inner2)));
    DIAMOND2(inner3, -1, 2, -1, 1);
    JT_ASSERT(~removePolygon(result, std::begin(inner3), std::end(inner3)));
    DIAMOND2(inner4, 1, 2, -1, 1);
    JT_ASSERT(~removePolygon(result, std::begin(inner4), std::end(inner4)));
}

static void test_ThreeSpokes()
{
    Dim2::PointD points[] = {
        Dim2::pointD( 2,  0),
        Dim2::pointD( 0,  0),
        Dim2::pointD(-1, -2),
        Dim2::pointD( 1, -2),
        Dim2::pointD( 0,  0),
        Dim2::pointD(-1,  1),
        Dim2::pointD(-2,  0),
        Dim2::pointD( 0,  0),
        Dim2::pointD( 1,  1),
        Dim2::pointD( 2,  0)
    };
    std::vector<std::vector<Dim2::PointD>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 4);
    Dim2::PointD outer[] = {
        Dim2::pointD( 0,  0),
        Dim2::pointD( 2,  0),
        Dim2::pointD( 1,  1),
        Dim2::pointD( 0,  0),
        Dim2::pointD(-1,  1),
        Dim2::pointD(-2,  0),
        Dim2::pointD( 0,  0),
        Dim2::pointD(-1, -2),
        Dim2::pointD( 1, -2),
        Dim2::pointD( 0,  0)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
}

static void test_SquareWithProtrudingLine()
{
    Dim2::PointD points[] = {
        Dim2::pointD(-2, -2),
        Dim2::pointD(-2,  0),
        Dim2::pointD( 4,  0),
        Dim2::pointD(-2,  0),
        Dim2::pointD(-2,  2),
        Dim2::pointD( 2,  2),
        Dim2::pointD( 2, -2),
        Dim2::pointD(-2, -2)
    };
    std::vector<std::vector<Dim2::PointD>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 3);
    Dim2::PointD outer[] = {
        Dim2::pointD( 2,  2),
        Dim2::pointD(-2,  2),
        Dim2::pointD(-2, -2),
        Dim2::pointD( 2, -2),
        Dim2::pointD( 2,  0),
        Dim2::pointD( 4,  0),
        Dim2::pointD( 2,  0),
        Dim2::pointD( 2,  2)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
}

JT_SUBTEST("Geometry",
           test_OverlappingSquareAndRect,
           test_FiveOverlappingSquares,
           test_Ribbon,
           test_ThreeSpokes,
           test_SquareWithProtrudingLine);
