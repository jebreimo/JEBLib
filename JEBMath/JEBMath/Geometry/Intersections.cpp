#include <utility>
#include "JEBBase/Algorithms/Sort.hpp"
#include "../Math/Comparisons.hpp"
#include "../Math/Utilities.hpp"
#include "Intersections.hpp"

namespace JEBMath {

bool containsPoint(const Line<double, 2>& l, const Vector<double, 2>& p, double epsilon)
{
    return fabs(getNormal(l.getVector()) * (p - l.getPoint())) <= epsilon;
}

bool containsPoint(const LineSegment<double, 2>& l, const Vector<double, 2>& p, double epsilon)
{
    auto lv = l.getVector();
    auto pv = p - l.getStart();
    return std::fabs(getNormal(lv) * pv) <= epsilon &&
           std::fabs(0.5 - (lv * pv) / getLengthSquared(lv)) <= 0.5 + epsilon;
}

bool areParallel(const LineSegment<double, 2>& a, const Line<double, 2>& b, double epsilon)
{
    double tmp = a.getVector() * getNormal(b.getVector());
    return std::fabs(tmp) <= epsilon;
}

bool areParallel(const Line<double, 2>& a, const Line<double, 2>& b, double epsilon)
{
    double tmp = a.getVector() * getNormal(b.getVector());
    return std::fabs(tmp) <= epsilon;
}

bool areCoincident(const Line<double, 2>& a, const Line<double, 2>& b, double epsilon)
{
    return containsPoint(a, b.getPoint(), epsilon) &&
           areParallel(a, b, epsilon);
}

LineRelationship intersection(double& offsetA,
                              const LineSegment<double, 2>& a,
                              const Line<double, 2>& b,
                              double epsilon)
{
    auto vA = a.getVector();
    auto nB = getNormal(b.getVector());

    double denominator = vA * nB;
    if (equal<double>(denominator, 0, epsilon))
        // Lines are parallel or overlapping. Overlapping lines are not
        // considered as intersecting.
        return NONINTERSECTING;

    auto vAB = b.getPoint() - a.getStart();
    offsetA = vAB * nB / denominator;
    return (0 <= offsetA && offsetA <= 1) ? INTERSECTING : NONINTERSECTING;
}

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const Line<double, 2>& a,
                              const Line<double, 2>& b,
                              double epsilon)
{
    auto vA = a.getVector();
    auto nB = getNormal(b.getVector());

    auto denominator = vA * nB;
    if (equal<double>(denominator, 0, epsilon))
    {
        if (equal<double>(nB * (a.getPoint() - b.getPoint()), epsilon))
          return OVERLAPPING;
        else
          return NONINTERSECTING;
    }

    auto nA = getNormal(a.getVector());

    auto vAB = b.getPoint() - a.getPoint();

    offsetA = vAB * nB / denominator;
    offsetB = vAB * nA / denominator;

    return INTERSECTING;
}

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const LineSegment<double, 2>& a,
                              const LineSegment<double, 2>& b,
                              double epsilon)
{
    LineRelationship res = intersection(offsetA, offsetB,
                                        Line<double, 2>(a), Line<double, 2>(b),
                                        epsilon);
    if (res == OVERLAPPING)
        return UNDETERMINED;
    else if (res == INTERSECTING &&
             inRange<double>(0, offsetA, 1, epsilon) &&
             inRange<double>(0, offsetB, 1, epsilon))
        return INTERSECTING;
    else
        return NONINTERSECTING;
}

LineRelationship intersection(Vector<double, 2>& intersectionPoint,
                              const LineSegment<double, 2>& a,
                              const LineSegment<double, 2>& b,
                              double epsilon)
{
    double offsetA, offsetB;
    LineRelationship result = intersection(offsetA, offsetB, a, b, epsilon);
    if (result == INTERSECTING)
        intersectionPoint = a.getPointAtT(offsetA);
    return result;
}

LineRelationship intersection(Vector<double, 2>& intersectionPoint,
                              const LineSegment<double, 2>& a,
                              const Line<double, 2>& b,
                              double epsilon)
{
    double offset;
    LineRelationship result = intersection(offset, a, b, epsilon);
    if (result == INTERSECTING)
        intersectionPoint = a.getPointAtT(offset);
    return result;
}

bool overlap(std::pair<double, double>& offsetsA,
             const LineSegment<double, 2>& a,
             const LineSegment<double, 2>& b,
             double epsilon)
{
    auto ta0 = a.getVector() * (b.getStart() - a.getStart()) / getLengthSquared(a.getVector());
    auto ta1 = a.getVector() * (b.getEnd() - a.getStart()) / getLengthSquared(a.getVector());
    if ((ta0 > 1 && ta1 > 1) || (ta0 < 0 && ta1 < 0))
        return false;
    offsetsA.first = getClamped(ta0, 0.0, 1.0);
    offsetsA.second = getClamped(ta1, 0.0, 1.0);
    return true;
}

bool overlap(std::pair<double, double>& offsetsA,
             std::pair<double, double>& offsetsB,
             const LineSegment<double, 2>& a,
             const LineSegment<double, 2>& b,
             double epsilon)
{
    if (!overlap(offsetsA, a, b, epsilon))
        return false;
    auto tb0 = b.getVector() * (a.getStart() - b.getStart()) / getLengthSquared(b.getVector());
    auto tb1 = b.getVector() * (a.getEnd() - b.getStart()) / getLengthSquared(b.getVector());
    if (offsetsA.first > offsetsA.second)
        std::swap(tb0, tb1);
    offsetsB.first = getClamped(tb0, 0.0, 1.0);
    offsetsB.second = getClamped(tb1, 0.0, 1.0);
    return true;
}

bool intersects(const LineSegment<double, 2>& a, const LineSegment<double, 2>& b, double epsilon)
{
  double offsetA, offsetB;
  return intersection(offsetA, offsetB, a, b, epsilon) == INTERSECTING;
}

bool intersects(const LineSegment<double, 2>& a, const Line<double, 2>& b, double epsilon)
{
    double offsetA;
    return intersection(offsetA, a, b, epsilon) == INTERSECTING;
}

bool intersects(const Line<double, 2>& a, const LineSegment<double, 2>& b, double epsilon)
{
    return intersects(b, a, epsilon);
}

//bool nextIntersection(size_t& intersectingSegment,
//                      const Line<double, 2>& line,
//                      const LineStringD& ls,
//                      const RangeS& lsRange)
//{
//  size_t iMax = std::min(ls.segmentCount(), lsRange.end);
//  for (size_t i = lsRange.start; i < iMax; ++i)
//  {
//    if (intersects(ls.segment(i), line))
//    {
//      intersectingSegment = i;
//      return true;
//    }
//  }
//  return false;
//}

}
