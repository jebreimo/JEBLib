#ifndef JEB_MATH_INTERSECTIONS_HPP
#define JEB_MATH_INTERSECTIONS_HPP

#include <cmath>
#include <limits>
#include "../Math/Constants.hpp"
#include "Line.hpp"
#include "LineString.hpp"

namespace JEBMath {

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
Side::Enum getSide(const Line<T, 2>& l, const Vector<T, 2>& p);

bool containsPoint(const Line<double, 2>& l,
                   const Vector<double, 2>& p,
                   double epsilon = 0);
bool containsPoint(const LineSegment<double, 2>& l,
                   const Vector<double, 2>& p,
                   double epsilon = 0);

bool areParallel(const LineSegment<double, 2>& a,
                 const Line<double, 2>& b,
                 double epsilon = 0);
bool areParallel(const Line<double, 2>& a,
                 const Line<double, 2>& b,
                 double epsilon = 0);
bool areCoincident(const Line<double, 2>& a,
                   const Line<double, 2>& b,
                   double epsilon = 0);

/** Returns the iterator at the first point between @a firstPoint and
  * @a lastPoint where the line segment between the point and its successor
  * intersects with @a lineSeg.
  *
  * @returns @a lastPoint if there are no intersections, otherwise an iterator
  *     to the first of the two successive points.
  */
template <typename BiIt>
BiIt findIntersection(LineSegment<double, 2> lineSeg,
                      BiIt firstPoint, BiIt lastPoint,
                      double epsilon);

bool intersects(const LineSegment<double, 2>& a,
                const LineSegment<double, 2>& b,
                double epsilon);
bool intersects(const LineSegment<double, 2>& a,
                const Line<double, 2>& b,
                double epsilon);
bool intersects(const Line<double, 2>& a,
                const LineSegment<double, 2>& b,
                double epsilon);

enum LineRelationship {
    NONINTERSECTING, //< Lines or line segments are parallel, but not colinear
    INTERSECTING, //< Lines or line segments are intersecting
    OVERLAPPING, //< Lines are colinear
    UNDETERMINED //< Line segments are colinear, and may or may not overlap
};

LineRelationship intersection(double& offsetA,
                              double& offsetB,
                              const Line<double, 2>& a,
                              const Line<double, 2>& b,
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
                              const LineSegment<double, 2>& a,
                              const LineSegment<double, 2>& b,
                              double epsilon);
LineRelationship intersection(Vector<double, 2>& intersectionPoint,
                              const LineSegment<double, 2>& a,
                              const LineSegment<double, 2>& b,
                              double epsilon);
LineRelationship intersection(Vector<double, 2>& intersectionPoint,
                              const LineSegment<double, 2>& a,
                              const Line<double, 2>& b,
                              double epsilon);
LineRelationship intersection(Vector<double, 2>& intersectionPoint,
                              const Line<double, 2>& a,
                              const LineSegment<double, 2>& b,
                              double epsilon);

bool overlap(std::pair<double, double>& offsetsA,
             const LineSegment<double, 2>& a,
             const LineSegment<double, 2>& b,
             double epsilon = 0);

/**
  * If @a a and @a b point in (even slightly) oposite directions,
  * @a first in @a offsetsA will be greater than @a second. In
  * @a offsetsB, @a first will always be smaller than or equal to
  * @a second.
  */
bool overlap(std::pair<double, double>& offsetsA,
             std::pair<double, double>& offsetsB,
             const LineSegment<double, 2>& a,
             const LineSegment<double, 2>& b,
             double epsilon = 0);

template <typename T>
bool areTangentialAtPoint(const Vector<T, 2>& point,
                          Vector<T, 2> fromA, Vector<T, 2> toA,
                          Vector<T, 2> fromB, Vector<T, 2> toB,
                          double epsilon = 0);

}

#include "Intersections-impl.hpp"

#endif
