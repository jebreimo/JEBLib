#ifndef JEB_MATH_INTERSECTIONS_HPP
#define JEB_MATH_INTERSECTIONS_HPP

#include <cmath>
#include <limits>
#include "JEBMath/Math/Constants.hpp"
#include "Types.hpp"

namespace JEBMath { namespace Dim2 {

namespace Side
{
    enum Enum
    {
        Neither,
        Left,
        Right,
        Both
    };
}

template <typename T>
Side::Enum side(const Line<T, 2>& l, const Point<T, 2>& p);

bool containsPoint(const LineD& l,
                   const PointD& p,
                   double epsilon = 0);
bool containsPoint(const LineSegmentD& l,
                   const PointD& p,
                   double epsilon = 0);

bool areParallel(const LineSegmentD& a, const LineD& b, double epsilon = 0);
bool areParallel(const LineD& a,
                 const LineD& b,
                 double epsilon = 0);
bool areCoincident(const LineD& a,
                   const LineD& b,
                   double epsilon = 0);

/** Returns the iterator at the first point between @a firstPoint and
  * @a lastPoint where the line segment between the point and its successor
  * intersects with @a lineSeg.
  *
  * @returns @a lastPoint if there are no intersections, otherwise an iterator
  *     to the first of the two successive points.
  */
template <typename BiIt>
BiIt findIntersection(LineSegmentD lineSeg,
                      BiIt firstPoint, BiIt lastPoint,
                      double epsilon);

bool intersects(const LineSegmentD& a, const LineSegmentD& b, double epsilon);
bool intersects(const LineSegmentD& a, const LineD& b, double epsilon);
bool intersects(const LineD& a, const LineSegmentD& b, double epsilon);

enum LineRelationship {
    Nonintersecting, //< Lines or line segments are parallel, but not colinear
    Intersecting, //< Lines or line segments are intersecting
    Overlapping, //< Lines are colinear
    Undetermined //< Line segments are colinear, and may or may not overlap
};

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const LineD& a,
                              const LineD& b,
                              double epsilon);

/**
  * @returns
  *   @arg Nonintersecting  @a a and @a b have no points in common
  *   @arg Intersecting   @a a and @a b have exactly one point in common
  *   @arg Undetermined   @a a and @a b are colinear and maybe overlapping.
  *                       Use overlap to calculate the offsets.
  */
LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const LineSegmentD& a,
                              const LineSegmentD& b,
                              double epsilon);
LineRelationship intersection(PointD& intersectionPoint,
                              const LineSegmentD& a,
                              const LineSegmentD& b,
                              double epsilon);
LineRelationship intersection(PointD& intersectionPoint,
                              const LineSegmentD& a,
                              const LineD& b,
                              double epsilon);
LineRelationship intersection(PointD& intersectionPoint,
                              const LineD& a,
                              const LineSegmentD& b,
                              double epsilon);

bool overlap(std::pair<double, double>& offsetsA,
             const LineSegmentD& a,
             const LineSegmentD& b,
             double epsilon = 0);

/**
  * If @a a and @a b point in (even slightly) oposite directions,
  * @a first in @a offsetsA will be greater than @a second. In
  * @a offsetsB, @a first will always be smaller than or equal to
  * @a second.
  */
bool overlap(std::pair<double, double>& offsetsA,
             std::pair<double, double>& offsetsB,
             const LineSegmentD& a,
             const LineSegmentD& b,
             double epsilon = 0);

template <typename T>
bool areTangentialAtPoint(const Point<T, 2>& point,
                          Point<T, 2> fromA, Point<T, 2> toA,
                          Point<T, 2> fromB, Point<T, 2> toB,
                          double epsilon = 0);

}}

#include "Intersections.impl.hpp"

#endif
