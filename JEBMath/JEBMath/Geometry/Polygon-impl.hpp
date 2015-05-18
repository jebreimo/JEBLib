#include <iterator>
#include <stdexcept>
#include "../Math/Comparisons.hpp"
#include "../Math/Utilities.hpp"
#include "Intersections.hpp"
#include "PolygonUnwinder.hpp"
#include "Vector.hpp"

namespace JEBMath { namespace Polygon {

namespace detail
{
    template <typename T>
    std::pair<Vector<T, 2>, Vector<T, 2>> sortedByY(const Vector<T, 2>& a,
                                                    const Vector<T, 2>& b)
    {
        if (getY(a) <= getY(b))
            return std::pair<Vector<T, 2>, Vector<T, 2>>(a, b);
        else
            return std::pair<Vector<T, 2>, Vector<T, 2>>(b, a);
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
        return getX(v0) * getY(v1) - getY(v0) * getX(v1);
    }

    template <typename T>
    T crossZ(const Vector<T, 2>& p0, const Vector<T, 2>& p1,
             const Vector<T, 2>& p2)
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
double getAngle(const Vector<T, 2>& p0,
                const Vector<T, 2>& p1,
                const Vector<T, 2>& p2)
{
    return getAngle(p0 - p1, p2 - p1);
}

template <typename T>
double getAngleCCW(const Vector<T, 2>& p0,
                   const Vector<T, 2>& p1,
                   const Vector<T, 2>& p2)
{
    int rot = getRotation(p0, p1, p2);
    double ang = getAngle(p0, p1, p2);
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
bool isPolygon(const std::vector<Vector<T, 2>>& poly)
{
    return isPolygon(begin(poly), end(poly));
}

template <typename T>
int getRotation(const Vector<T, 2>& p0,
                const Vector<T, 2>& p1,
                const Vector<T, 2>& p2)
{
    return int(getSign(detail::crossZ(p0, p1, p2)));
}

template <typename T>
Side getDirection(const Vector<T, 2>& v0,
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
Side getDirection(const Vector<T, 2>& p0,
                  const Vector<T, 2>& p1,
                  const Vector<T, 2>& p2,
                  double tolerance)
{
    return getDirection(p1 - p0, p2 - p1, tolerance);
}

template <typename It>
double getArea(It begin, It end)
{
    if (!isPolygon(begin, end))
        throw std::invalid_argument("invalid polygon");
    double sum = 0;
    It it2 = begin;
    It it1 = it2++;
    while (it2 != end)
    {
        sum += getX(*it1) * getY(*it2) - getX(*it2) * getY(*it1);
        ++it1, ++it2;
    }
    return sum / 2;
}

template <typename T>
double getArea(const std::vector<Vector<T, 2>>& poly)
{
    return getArea(poly.begin(), poly.end());
}

template <typename T>
bool isConvex(const std::vector<Vector<T, 2>>& poly)
{
    if (poly.size() < 4)
        throw std::invalid_argument("invalid polygon");

    auto it = poly.begin();

    int sign = getRotation(*(poly.end() - 2), *it, *(it + 1));

    for (++it; it != poly.end() - 1; it++)
    {
        int newSign = getRotation(*(it - 1), *it, *(it + 1));
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
bool isCCW(const std::vector<Vector<T, 2>>& poly)
{
    return isCCW(poly.begin(), poly.end());
}

template <typename T>
PolygonPosition::Type isInside(const std::vector<Vector<T, 2>>& poly,
                               const Vector<T, 2>& point)
{
    if (poly.size() < 4)
        throw std::invalid_argument("invalid polygon");

    // Count the number of times a horizontal line extending left from the
    // point intersects an edge segment in the polygon.
    int intersections = 0;
    for (auto it = poly.begin() + 1; it != poly.end(); it++)
    {
        std::pair<Vector<T, 2>, Vector<T, 2>> points =
                    detail::sortedByY(*(it - 1), *it);

        if (getY(points.first) < getY(point) && getY(point) <= getY(points.second))
        {
            T t = (getY(point) - getY(points.first)) /
                  (getY(points.second) - getY(points.first));
            T xt = getX(points.first) + t * (getX(points.second) - getX(points.first));
            if (equal(getX(point), xt))
                return PolygonPosition::OnBorder;
            else if (getX(point) > xt)
                intersections++;
        }
        else if (getY(points.first) == getY(point))
        {
            // If the point coincide with a vertex in the polygon.
            if (getX(points.first) == getX(point))
                return PolygonPosition::OnBorder;
            // If the point  lie on a horizontal edge in the polygon.
            else if (getY(points.first) == getY(points.second) &&
                     detail::between(getX(point),
                                     getX(points.first), getX(points.second)))
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
    if (findIntersection(makeLineSegment(*it, *std::next(it)),
                         std::next(it, 2), cmpEnd, 0) != cmpEnd)
        return true;
    auto itEnd = cmpEnd++;
    for (++it; it != itEnd; ++it)
    {
        if (findIntersection(makeLineSegment(*it, *std::next(it)),
                             std::next(it, 2), cmpEnd, 0) != cmpEnd)
            return true;
    }
    return false;
}

template <typename T>
bool isSelfIntersecting(const std::vector<Vector<T, 2>>& poly)
{
    return isSelfIntersecting(begin(poly), end(poly));
}

template <typename PointIt>
PointIt increment(PointIt& it, PointIt end)
{
    PointIt prev = it++;
    while (it != end && *it == *prev)
        ++it;
    return prev;
}

template <typename PointIt, typename T>
std::pair<PointIt, double> findFirst(PointIt beg, PointIt end, double offset,
                                     const Vector<T, 2>& point,
                                     double tolerance)
{
    if ((beg == end) ||
        (offset == 0 && areEquivalent(point, *beg, tolerance)))
        return std::make_pair(beg, 0.0);

    PointIt prev = increment(beg, end);
    while (beg != end)
    {
        if (offset == 0.0 && areEquivalent(*beg, point, tolerance))
            return std::make_pair(beg, 0.0);
        auto lineSeg = makeLineSegment(*prev, *beg);
        auto relPos = getRelativePosition(lineSeg, point);
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
         !areEquivalent(*beg, *cmpBeg, tolerance)))
    {
        return std::make_pair(std::make_pair(beg, offset),
                              std::make_pair(cmpBeg, cmpOffset));
    }
    PointIt1 prev = increment(beg, end);
    PointIt2 cmpPrev = increment(cmpBeg, cmpEnd);
    while (beg != end && cmpBeg != cmpEnd)
    {
        if (areEquivalent(*beg, *cmpBeg, tolerance))
        {
            prev = increment(beg, end);
            cmpPrev = increment(cmpBeg, cmpEnd);
            offset = cmpOffset = 0;
        }
        else
        {
            auto lineSeg = makeLineSegment(*cmpPrev, *cmpBeg);
            auto relPos = getRelativePosition(lineSeg, *beg);
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
                auto lineSeg = makeLineSegment(*prev, *beg);
                auto relPos = getRelativePosition(lineSeg, *cmpBeg);
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
bool areEquivalent(PointIt1 beg, PointIt1 end,
                   PointIt2 cmpBeg, PointIt2 cmpEnd,
                   double tolerance)
{
    if (beg == end)
        return cmpBeg == cmpEnd;

    PointIt2 cmpIt = cmpBeg;
    while (true)
    {
        auto match = findFirst(cmpIt, cmpEnd, 0, *beg, tolerance);
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
std::vector<Vector<double, 2>> getHull(PointIt begin, PointIt end,
                                       double tolerance)
{
    Unwinder unwinder;
    unwinder.setTolerance(tolerance);
    unwinder.setPolygon(begin, end);
    return unwinder.getHull();
}

template <typename PointIt>
std::vector<std::vector<Vector<double, 2>>> split(PointIt begin, PointIt end,
                                                  double tolerance)
{
    Unwinder unwinder;
    unwinder.setTolerance(tolerance);
    unwinder.setPolygon(begin, end);
    return unwinder.split();
}

}}
