#include <utility>
#include "JEBBase/Algorithms/Sort.hpp"
#include "JEBMath/Math/Comparisons.hpp"
#include "Intersections.hpp"

namespace JEBMath { namespace Dim2 {

bool containsPoint(const LineD& l, const PointD& p, double epsilon)
{
    return fabs(normal(l.vector()) * (p - l.point())) <= epsilon;
}

bool containsPoint(const LineSegmentD& l, const PointD& p, double epsilon)
{
    VectorD lv = l.vector();
    VectorD pv = p - l.start();
    return fabs(normal(lv) * pv) <= epsilon &&
           fabs(0.5 - (lv * pv) / lengthSquared(lv)) <= 0.5 + epsilon;
}

bool areParallel(const LineSegmentD& a, const LineD& b, double epsilon)
{
    double tmp = a.vector() * normal(b.vector());
    return std::fabs(tmp) <= epsilon;
}

bool areParallel(const LineD& a, const LineD& b, double epsilon)
{
    double tmp = a.vector() * normal(b.vector());
    return std::fabs(tmp) <= epsilon;
}

bool areCoincident(const LineD& a, const LineD& b, double epsilon)
{
    return containsPoint(a, b.point(), epsilon) &&
           areParallel(a, b, epsilon);
}

LineRelationship intersection(double& offsetA,
                              const LineSegmentD& a,
                              const LineD& b,
                              double epsilon)
{
    VectorD vA = a.vector();
    VectorD nB = normal(b.vector());

    double denominator = vA * nB;
    if (equal<double>(denominator, 0, epsilon))
        // Lines are parallel or overlapping. Overlapping lines are not
        // considered as intersecting.
        return Nonintersecting;

    VectorD vAB = b.point() - a.start();
    offsetA = vAB * nB / denominator;
    return (0 <= offsetA && offsetA <= 1) ? Intersecting : Nonintersecting;
}

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const LineD& a,
                              const LineD& b,
                              double epsilon)
{
    VectorD vA = a.vector();
    VectorD nB = normal(b.vector());

    double denominator = vA * nB;
    if (equal<double>(denominator, 0, epsilon))
    {
        if (equal<double>(nB * (a.point() - b.point()), epsilon))
          return Overlapping;
        else
          return Nonintersecting;
    }

    VectorD nA = normal(a.vector());

    VectorD vAB = b.point() - a.point();

    offsetA = vAB * nB / denominator;
    offsetB = vAB * nA / denominator;

    return Intersecting;
}

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const LineSegmentD& a,
                              const LineSegmentD& b,
                              double epsilon)
{
    LineRelationship res = intersection(offsetA, offsetB,
                                        LineD(a), LineD(b),
                                        epsilon);
    if (res == Overlapping)
        return Undetermined;
    else if (res == Intersecting &&
             inRange<double>(0, offsetA, 1, epsilon) &&
             inRange<double>(0, offsetB, 1, epsilon))
        return Intersecting;
    else
        return Nonintersecting;
}

LineRelationship intersection(PointD& intersectionPoint,
                              const LineSegmentD& a,
                              const LineSegmentD& b,
                              double epsilon)
{
    double offsetA, offsetB;
    LineRelationship result = intersection(offsetA, offsetB, a, b, epsilon);
    if (result == Intersecting)
        intersectionPoint = a.pointAtT(offsetA);
    return result;
}

LineRelationship intersection(PointD& intersectionPoint,
                              const LineSegmentD& a,
                              const LineD& b,
                              double epsilon)
{
    double offset;
    LineRelationship result = intersection(offset, a, b, epsilon);
    if (result == Intersecting)
        intersectionPoint = a.pointAtT(offset);
    return result;
}

static double restrictValue(double value)
{
    if (value < 0)
        return 0;
    else if (value > 1)
        return 1;
    else
        return value;
}

bool overlap(std::pair<double, double>& offsetsA,
             const LineSegmentD& a,
             const LineSegmentD& b,
             double epsilon)
{
    double ta0 = a.vector() * (b.start() - a.start()) / lengthSquared(a.vector());
    double ta1 = a.vector() * (b.end() - a.start()) / lengthSquared(a.vector());
    if ((ta0 > 1 && ta1 > 1) || (ta0 < 0 && ta1 < 0))
        return false;
    offsetsA.first = restrictValue(ta0);
    offsetsA.second = restrictValue(ta1);
    return true;
}

bool overlap(std::pair<double, double>& offsetsA,
             std::pair<double, double>& offsetsB,
             const LineSegmentD& a,
             const LineSegmentD& b,
             double epsilon)
{
    if (!overlap(offsetsA, a, b, epsilon))
        return false;
    double tb0 = b.vector() * (a.start() - b.start()) / lengthSquared(b.vector());
    double tb1 = b.vector() * (a.end() - b.start()) / lengthSquared(b.vector());
    if (offsetsA.first > offsetsA.second)
        std::swap(tb0, tb1);
    offsetsB.first = restrictValue(tb0);
    offsetsB.second = restrictValue(tb1);
    return true;
}

bool intersects(const LineSegmentD& a, const LineSegmentD& b, double epsilon)
{
  double offsetA, offsetB;
  return intersection(offsetA, offsetB, a, b, epsilon) == Intersecting;
}

bool intersects(const LineSegmentD& a, const LineD& b, double epsilon)
{
    double offsetA;
    return intersection(offsetA, a, b, epsilon) == Intersecting;
}

bool intersects(const LineD& a, const LineSegmentD& b, double epsilon)
{
    return intersects(b, a, epsilon);
}

//bool nextIntersection(size_t& intersectingSegment,
//                      const LineD& line,
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

}}
