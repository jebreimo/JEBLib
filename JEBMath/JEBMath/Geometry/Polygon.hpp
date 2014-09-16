#ifndef JEB_MATH_POLYGON_HPP
#define JEB_MATH_POLYGON_HPP
#include <vector>
#include "Point.hpp"
#include "Types.hpp"

namespace JEBMath { namespace Polygon {

template <typename FwdIt>
bool isPolygon(FwdIt begin, FwdIt end);

template <typename T>
bool isPolygon(const std::vector<Point<T, 2>>& poly);

template <typename T>
bool isConvex(const std::vector<Point<T, 2>>& poly);

/** @brief Returns true if the polygon from @a begin to @a end
 *      is counter-clockwise.
 *
 *  It must be an input iterator over a collection of points of 2
 *  dimensions or more. The functions x(*begin) and y(*begin) are
 *  used to determine the points' coordinates.
 *  @throw std::invalid_argument if the iterator range has less than four
 *      points or the first and last points are not the same.
 */
template <typename It>
bool isCCW(It begin, It end);

template <typename T>
bool isCCW(const std::vector<Point<T, 2>>& poly);

template <typename BiIt>
bool isSelfIntersecting(BiIt first, BiIt last);

template <typename T>
bool isSelfIntersecting(const std::vector<Point<T, 2>>& poly);

/** @brief Determines the direction of three points.
 *
 *  The function determines the direction of the points in the
 *  order they are given.
 *  @return @arg -1 Points are counter-clockwise
 *          @arg  0 Points are colinear
 *          @arg  1 Points rotate clockwise.
 */
template <typename T>
int rotation(const Point<T, 2>& p0,
             const Point<T, 2>& p1,
             const Point<T, 2>& p2);

enum Side
{
    Undetermined = 0,
    Left = 1,
    Right = 2,
    Ahead = 4,
    Behind = 8
};

template <typename T>
Side direction(const Vector<T, 2>& v0,
               const Vector<T, 2>& p1,
               double tolerance);

/** @brief Determines the position of @a p2 relative to the line through
 *      @a p0 and @p1.
 *
 *  @return @arg 0 @a p2 is right of
 *          @arg 1 Points are colinear, non-overlapping
 *          @arg 2 Points rotate clockwise.
 *          @arg 3 Points are colinear, overlapping
 *          @arg 4 @a p0 or @a p2 coincide with @a p1
 */
template <typename T>
Side direction(const Point<T, 2>& p0,
               const Point<T, 2>& p1,
               const Point<T, 2>& p2,
               double tolerance);

template <typename T>
double angle(const Point<T, 2>& p0,
             const Point<T, 2>& p1,
             const Point<T, 2>& p2);

template <typename T>
double angleCCW(const Point<T, 2>& p0,
                const Point<T, 2>& p1,
                const Point<T, 2>& p2);

template <typename T>
double area(const std::vector<Point<T, 2>>& poly);

template <typename It>
double area(It begin, It end);

template <typename T>
std::vector<Point<T, 2>> unwind(const std::vector<Point<T, 2>>& poly);

namespace PolygonPosition
{
    enum Type
    {
        Outside,
        Inside,
        OnBorder
    };
}

/** @brief Returns whether @a point is inside or outside @a poly.
 *  @param poly a polygon of at least four points, the last point must
 *         be the same as the first, otherwise the function can return
 *         an incorrect result.
 *  @throw std::invalid_argument if @a poly has less than 4 points.
 */
template <typename T>
PolygonPosition::Type isInside(const std::vector<Point<T, 2>>& poly,
                               const Point<T, 2>& point);

template <typename PointIt>
std::vector<Dim2::PointD> hull(PointIt begin, PointIt end, double tolerance);

template <typename PointIt>
std::vector<std::vector<Dim2::PointD>> split(PointIt begin, PointIt end,
                                           double tolerance);

template <typename PointIt1, typename PointIt2>
bool equivalent(PointIt1 beg, PointIt1 end,
                PointIt2 cmpBeg, PointIt2 cmpEnd,
                double tolerance = 0);

// template <typename T>
// class CombinedPolygon
// {
// public:
//     typedef Point<T, 2> Point;
//     typedef std::vector<Point> Polygon;

//     CombinedPolygon(const Polygon& first,
//                     const Polygon& second);

//     void union(std::list<Polygon>& result) const;
//     void intersection(std::list<Polygon>& result) const;
//     void firstOnly(std::list<Polygon>& result) const;
//     void secondOnly(std::list<Polygon>& result) const;
// private:
//     struct PointD
//     {
//         PointD* next;
//         PointD* prev;
//         PointD* other;
//         Point point;
//         bool entrance;
//     };
// };
}}

#include "Polygon.impl.hpp"

#endif
