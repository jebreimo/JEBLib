#include <iterator>
#include <stdexcept>
#include "JEBMath/Math/Comparisons.hpp"
#include "JEBMath/Math/Utilities.hpp"
#include "Intersections.hpp"
#include "PolygonUnwinder.hpp"
#include "Vector.hpp"

namespace JEBMath { namespace Polygon {

namespace detail
{
    template <typename T>
    std::pair<Point<T, 2>, Point<T, 2>> sortedByY(const Point<T, 2>& a,
                                                  const Point<T, 2>& b)
    {
        if (y(a) <= y(b))
            return std::pair<Point<T, 2>, Point<T, 2>>(a, b);
        else
            return std::pair<Point<T, 2>, Point<T, 2>>(b, a);
    }

    template <typename T>
    bool between(T value, T rangeStart, T rangeEnd)
    {
        if (rangeEnd < rangeStart)
            std::swap(rangeStart, rangeEnd);
        return rangeStart <= value && value <= rangeEnd;
    }

    template <typename T>
    T crossZ(const Vector<T, 2>& v0, const Vector<T, 2>& v1)
    {
        return x(v0) * y(v1) - y(v0) * x(v1);
    }

    template <typename T>
    T crossZ(const Point<T, 2>& p0, const Point<T, 2>& p1,
             const Point<T, 2>& p2)
    {
        return crossZ(p1 - p0, p2 - p1);
    }

    template <typename FwdIt>
    bool isPolygon(FwdIt begin, FwdIt end, std::forward_iterator_tag)
    {
        size_t n = 0;
        FwdIt last = begin;
        for (FwdIt it = begin; it != end; last = it++)
            ++n;
        return n >= 4 && *begin == *last;
    }

    template <typename RndIt>
    bool isPolygon(RndIt begin, RndIt end, std::random_access_iterator_tag)
    {
        return std::distance(begin, end) >= 4 && *begin == *std::prev(end);
    }
}

template <typename T>
double angle(const Point<T, 2>& p0,
             const Point<T, 2>& p1,
             const Point<T, 2>& p2)
{
    return angle(p0 - p1, p2 - p1);
}

template <typename T>
double angleCCW(const Point<T, 2>& p0,
                const Point<T, 2>& p1,
                const Point<T, 2>& p2)
{
    int rot = rotation(p0, p1, p2);
    double ang = angle(p0, p1, p2);
    if (rot >= 0)
        return ang;
    else
        return 2 * Pi - ang;
}

template <typename FwdIt>
bool isPolygon(FwdIt begin, FwdIt end)
{
    return detail::isPolygon(
            begin, end,
            typename std::iterator_traits<FwdIt>::iterator_category());
}

template <typename T>
bool isPolygon(const std::vector<Point<T, 2>>& poly)
{
    return isPolygon(begin(poly), end(poly));
}

template <typename T>
int rotation(const Point<T, 2>& p0,
             const Point<T, 2>& p1,
             const Point<T, 2>& p2)
{
    return (int)getSign(detail::crossZ(p0, p1, p2));
}

template <typename T>
Side direction(const Vector<T, 2>& v0,
               const Vector<T, 2>& v1,
               double tolerance)
{
    T value = detail::crossZ(v0, v1);
    if (equal<double>(value, 0, tolerance))
    {
        value = v0 * v1;
        if (equal<double>(value, 0, tolerance))
            return Undetermined;
        return value > 0 ? Ahead : Behind;
    }
    return value > 0 ? Left : Right;
}

template <typename T>
Side direction(const Point<T, 2>& p0,
               const Point<T, 2>& p1,
               const Point<T, 2>& p2,
               double tolerance)
{
    return direction(p1 - p0, p2 - p1, tolerance);
}

template <typename It>
double area(It begin, It end)
{
    if (!isPolygon(begin, end))
        throw std::invalid_argument("invalid polygon");
    double sum = 0;
    It it2 = begin;
    It it1 = it2++;
    while (it2 != end)
    {
        sum += x(*it1) * y(*it2) - x(*it2) * y(*it1);
        ++it1, ++it2;
    }
    return sum / 2;
}

template <typename T>
double area(const std::vector<Point<T, 2>>& poly)
{
    return area(poly.begin(), poly.end());
    // if (poly.size() < 4)
    //     throw std::invalid_argument("invalid polygon");
    // double sum = 0;
    // for (auto it = poly.begin() + 1; it != poly.end(); ++it)
    //     sum += x(*(it- 1)) * y(*it) - x(*it) * y(*(it - 1));
    // return sum / 2;
}

template <typename T>
bool isConvex(const std::vector<Point<T, 2>>& poly)
{
    if (poly.size() < 4)
        throw std::invalid_argument("invalid polygon");

    auto it = poly.begin();

    int sign = rotation(*(poly.end() - 2), *it, *(it + 1));

    for (++it; it != poly.end() - 1; it++)
    {
        int newSign = rotation(*(it - 1), *it, *(it + 1));
        if (sign == 0)
            sign = newSign;
        else if (newSign != 0 && newSign != sign)
            return false;
    }

    return true;
}

template <typename It>
bool isCCW(It begin, It end)
{
    return area(begin, end) >= 0;
}

template <typename T>
bool isCCW(const std::vector<Point<T, 2>>& poly)
{
    return isCCW(poly.begin(), poly.end());
}

template <typename T>
PolygonPosition::Type isInside(const std::vector<Point<T, 2>>& poly,
                               const Point<T, 2>& point)
{
    if (poly.size() < 4)
        throw std::invalid_argument("invalid polygon");

    // Count the number of times a horizontal line extending left from the
    // point intersects an edge segment in the polygon.
    int intersections = 0;
    for (auto it = poly.begin() + 1; it != poly.end(); it++)
    {
        std::pair<Point<T, 2>, Point<T, 2>> points =
                    detail::sortedByY(*(it - 1), *it);

        if (y(points.first) < y(point) && y(point) <= y(points.second))
        {
            T t = (y(point) - y(points.first)) /
                  (y(points.second) - y(points.first));
            T xt = x(points.first) + t * (x(points.second) - x(points.first));
            if (equal(x(point), xt))
                return PolygonPosition::OnBorder;
            else if (x(point) > xt)
                intersections++;
        }
        else if (y(points.first) == y(point))
        {
            // If the point coincide with a vertex in the polygon.
            if (x(points.first) == x(point))
                return PolygonPosition::OnBorder;
            // If the point  lie on a horizontal edge in the polygon.
            else if (y(points.first) == y(points.second) &&
                     detail::between(x(point),
                                     x(points.first), x(points.second)))
                return PolygonPosition::OnBorder;

        }
    }

    return (intersections & 1) ? PolygonPosition::Inside
                               : PolygonPosition::Outside;
}

template <typename BiIt>
bool isSelfIntersecting(BiIt first, BiIt last)
{
    if (!isPolygon(first, last))
        return false;
    auto cmpEnd = std::prev(last, 2);
    auto it = first;
    if (Dim2::findIntersection(Dim2::LineSegmentD(*it, *std::next(it)),
                             std::next(it, 2), cmpEnd, 0) != cmpEnd)
        return true;
    auto itEnd = cmpEnd++;
    for (++it; it != itEnd; ++it)
    {
        if (Dim2::findIntersection(Dim2::LineSegmentD(*it, *std::next(it)),
                                 std::next(it, 2), cmpEnd, 0) != cmpEnd)
            return true;
    }
    return false;
}

template <typename T>
bool isSelfIntersecting(const std::vector<Point<T, 2>>& poly)
{
    return isSelfIntersecting(begin(poly), end(poly));
}

template <typename PointIt>
PointIt increment(PointIt& it, PointIt end)
{
    PointIt prev = it++;
    while (it != end && point2(*it) == point2(*prev))
        ++it;
    return prev;
}

template <typename PointIt, typename T>
std::pair<PointIt, double> findFirst(PointIt beg, PointIt end, double offset,
                                     const Point<T, 2>& point,
                                     double tolerance)
{
    if ((beg == end) ||
        (offset == 0 && equivalent(point, point2(*beg), tolerance)))
        return std::make_pair(beg, 0.0);

    PointIt prev = increment(beg, end);
    while (beg != end)
    {
        if (offset == 0.0 && equivalent(point2(*beg), point, tolerance))
            return std::make_pair(beg, 0.0);
        auto lineSeg = lineSegment(point2(*prev), point2(*beg));
        auto relPos = relativePosition(lineSeg, point);
        if (fabs(relPos[1]) <= tolerance &&
            inRange(offset, relPos[0], 1.0, tolerance))
        {
            return std::make_pair(prev, relPos[0]);
        }
        prev = increment(beg, end);
        offset = 0.0;
    }
    return std::make_pair(beg, 0.0);
}

template <typename PointIt1, typename PointIt2>
std::pair<std::pair<PointIt1, double>, std::pair<PointIt2, double>>
overlap(PointIt1 beg, PointIt1 end, double offset,
        PointIt2 cmpBeg, PointIt2 cmpEnd, double cmpOffset,
        double tolerance)
{
    if (beg == end || cmpBeg == cmpEnd ||
        (offset == 0 && cmpOffset == 0 &&
         !equivalent(point2(*beg), point2(*cmpBeg), tolerance)))
    {
        return std::make_pair(std::make_pair(beg, offset),
                              std::make_pair(cmpBeg, cmpOffset));
    }
    PointIt1 prev = increment(beg, end);
    PointIt2 cmpPrev = increment(cmpBeg, cmpEnd);
    while (beg != end && cmpBeg != cmpEnd)
    {
        if (equivalent(point2(*beg), point2(*cmpBeg), tolerance))
        {
            prev = increment(beg, end);
            cmpPrev = increment(cmpBeg, cmpEnd);
            offset = cmpOffset = 0;
        }
        else
        {
            auto lineSeg = lineSegment(point2(*cmpPrev), point2(*cmpBeg));
            auto relPos = relativePosition(lineSeg, point2(*beg));
            if (fabs(relPos[1]) > tolerance ||
                less<double>(relPos[0], cmpOffset, tolerance))
            {
                break;
            }

            if (less<double>(relPos[0], 1, tolerance))
            {
                offset = 0;
                cmpOffset = relPos[0];
                prev = increment(beg, end);
            }
            else
            {
                auto lineSeg = lineSegment(point2(*prev), point2(*beg));
                auto relPos = relativePosition(lineSeg, point2(*cmpBeg));
                if (!inRange<double>(offset, relPos[0], 1, tolerance))
                    break;
                offset = relPos[0];
                cmpOffset = 0;
                cmpPrev = increment(cmpBeg, cmpEnd);
            }
        }
    }
    return std::make_pair(std::make_pair(prev, offset),
                          std::make_pair(cmpPrev, cmpOffset));
}

template <typename PointIt>
bool isLastSegment(PointIt it, PointIt end)
{
    return it == end || ++it == end;
}

template <typename PointIt1, typename PointIt2>
bool equivalent(PointIt1 beg, PointIt1 end,
                PointIt2 cmpBeg, PointIt2 cmpEnd,
                double tolerance)
{
    if (beg == end)
        return cmpBeg == cmpEnd;

    PointIt2 cmpIt = cmpBeg;
    while (true)
    {
        auto match = findFirst(cmpIt, cmpEnd, 0, point2(*beg), tolerance);
        if (match.first == cmpEnd)
            return false;
        auto match2 = overlap(beg, end, 0,
                              match.first, cmpEnd, match.second,
                              tolerance);
        if (isLastSegment(match2.second.first, cmpEnd))
        {
            match2 = overlap(match2.first.first, end, match2.first.second,
                             cmpBeg, match2.second.first, 0,
                             tolerance);
            if (isLastSegment(match2.first.first, end) &&
                isLastSegment(match2.second.first, match.first) &&
                match2.second.second == match.second)
            {
                return true;
            }
        }
        cmpIt = ++match.first;
    }
    return false;
}

template <typename PointIt>
std::vector<Dim2::PointD> hull(PointIt begin, PointIt end, double tolerance)
{
    Unwinder unwinder;
    unwinder.setTolerance(tolerance);
    unwinder.setPolygon(begin, end);
    return unwinder.hull();
}

template <typename PointIt>
std::vector<std::vector<Dim2::PointD>> split(PointIt begin, PointIt end,
                                           double tolerance)
{
    Unwinder unwinder;
    unwinder.setTolerance(tolerance);
    unwinder.setPolygon(begin, end);
    return unwinder.split();
}

}}
