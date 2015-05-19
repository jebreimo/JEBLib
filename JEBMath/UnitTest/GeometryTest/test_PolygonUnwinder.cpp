#include "JEBMath/Geometry/Polygon.hpp"
#include <iterator>
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

template <typename It>
static size_t removePolygon(std::vector<std::vector<Vector<double, 2>>>& result,
                            It polyBegin, It polyEnd)
{
    size_t i = 0;
    for (auto it = result.begin(); it != result.end(); ++it)
    {
        if (Polygon::areEquivalent(it->begin(), it->end(),
                                   polyBegin, polyEnd, 1e-9))
        {
            result.erase(it);
            return i;
        }
        ++i;
    }
    return ~(size_t)0;
}

#define RECTANGLE2(name, x, y, w, h) \
    Vector<double, 2> name[] = { \
        vector2<double>(x, y), \
        vector2<double>(x + w, y), \
        vector2<double>(x + w, y + h), \
        vector2<double>(x, y + h), \
        vector2<double>(x, y) \
    }

static void test_OverlappingSquareAndRect()
{
    Vector<double, 3> points[] = {
        vector3<double>(-2, -2, 5),
        vector3<double>( 2, -2, 3),
        vector3<double>( 2,  3, 5),
        vector3<double>(-2,  3, 5),
        vector3<double>(-2, -3, 3),
        vector3<double>( 2, -3, 3),
        vector3<double>( 2,  2, 5),
        vector3<double>(-2,  2, 5),
        vector3<double>(-2, -2, 5)
    };
    RECTANGLE2(outer, 2, 3, -4, -6);
    RECTANGLE2(inner0, -2, 3, 4, -1);
    RECTANGLE2(inner1, -2, 2, 4, -4);
    RECTANGLE2(inner2, -2, -2, 4, -1);

    std::vector<std::vector<Vector<double, 2>>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 4);
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    JT_ASSERT(~removePolygon(result, std::begin(inner0), std::end(inner0)));
    JT_ASSERT(~removePolygon(result, std::begin(inner1), std::end(inner1)));
    JT_ASSERT(~removePolygon(result, std::begin(inner2), std::end(inner2)));
}

static void test_FiveOverlappingSquares()
{
    Vector<double, 2> points[] = {
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  0),
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2)
    };
    std::vector<std::vector<Vector<double, 2>>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 2);
    RECTANGLE2(outer, 2, 2, -4, -4);
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    RECTANGLE2(inner, -2, 2, 4, -4);
    JT_ASSERT(~removePolygon(result, std::begin(inner), std::end(inner)));
}

#define DIAMOND2(name, x, y, w, h) \
    Vector<double, 2> name[] = { \
        vector2<double>(x, y - h), \
        vector2<double>(x + w, y), \
        vector2<double>(x, y + h), \
        vector2<double>(x - w, y), \
        vector2<double>(x, y - h) \
    }

static void test_Ribbon()
{
    //    /\/\
    //    \/\/
    //    /\/\
    //   / /\ \
    //  /  --  \
    //  --------
    Vector<double, 2> points[] = {
        vector2<double>(-2,  2),
        vector2<double>(-1,  3),
        vector2<double>( 4, -2),
        vector2<double>(-4, -2),
        vector2<double>( 1,  3),
        vector2<double>( 2,  2),
        vector2<double>(-1, -1),
        vector2<double>( 1, -1),
        vector2<double>(-2,  2),
    };
    std::vector<std::vector<Vector<double, 2>>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 6);
    Vector<double, 2> outer[] = {
        vector2<double>(-4, -2),
        vector2<double>( 4, -2),
        vector2<double>( 1,  1),
        vector2<double>( 2,  2),
        vector2<double>( 1,  3),
        vector2<double>( 0,  2),
        vector2<double>(-1,  3),
        vector2<double>(-2,  2),
        vector2<double>(-1,  1),
        vector2<double>(-4, -2)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
    Vector<double, 2> inner0[] = {
        vector2<double>(-4, -2),
        vector2<double>(-1,  1),
        vector2<double>( 0,  0),
        vector2<double>(-1, -1),
        vector2<double>( 1, -1),
        vector2<double>( 0,  0),
        vector2<double>( 1,  1),
        vector2<double>( 4, -2),
        vector2<double>(-4, -2)
    };
    JT_ASSERT(~removePolygon(result, std::begin(inner0), std::end(inner0)));
    Vector<double, 2> inner1[] = {
        vector2<double>(-1, -1),
        vector2<double>( 0,  0),
        vector2<double>( 1, -1),
        vector2<double>(-1, -1)
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
    Vector<double, 2> points[] = {
        vector2<double>( 2,  0),
        vector2<double>( 0,  0),
        vector2<double>(-1, -2),
        vector2<double>( 1, -2),
        vector2<double>( 0,  0),
        vector2<double>(-1,  1),
        vector2<double>(-2,  0),
        vector2<double>( 0,  0),
        vector2<double>( 1,  1),
        vector2<double>( 2,  0)
    };
    std::vector<std::vector<Vector<double, 2>>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 4);
    Vector<double, 2> outer[] = {
        vector2<double>( 0,  0),
        vector2<double>( 2,  0),
        vector2<double>( 1,  1),
        vector2<double>( 0,  0),
        vector2<double>(-1,  1),
        vector2<double>(-2,  0),
        vector2<double>( 0,  0),
        vector2<double>(-1, -2),
        vector2<double>( 1, -2),
        vector2<double>( 0,  0)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
}

static void test_SquareWithProtrudingLine()
{
    Vector<double, 2> points[] = {
        vector2<double>(-2, -2),
        vector2<double>(-2,  0),
        vector2<double>( 4,  0),
        vector2<double>(-2,  0),
        vector2<double>(-2,  2),
        vector2<double>( 2,  2),
        vector2<double>( 2, -2),
        vector2<double>(-2, -2)
    };
    std::vector<std::vector<Vector<double, 2>>> result = Polygon::split(
            std::begin(points), std::end(points), 1e-9);
    JT_EQUAL(result.size(), 3);
    Vector<double, 2> outer[] = {
        vector2<double>( 2,  2),
        vector2<double>(-2,  2),
        vector2<double>(-2, -2),
        vector2<double>( 2, -2),
        vector2<double>( 2,  0),
        vector2<double>( 4,  0),
        vector2<double>( 2,  0),
        vector2<double>( 2,  2)
    };
    JT_EQUAL(removePolygon(result, std::begin(outer), std::end(outer)), 0);
}

JT_SUBTEST("Geometry",
           test_OverlappingSquareAndRect,
           test_FiveOverlappingSquares,
           test_Ribbon,
           test_ThreeSpokes,
           test_SquareWithProtrudingLine);
