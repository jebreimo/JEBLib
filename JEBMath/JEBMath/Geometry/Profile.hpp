#ifndef JEB_MATH_PROFILE_HPP
#define JEB_MATH_PROFILE_HPP

#include "Intersections.hpp"

namespace JEBMath { namespace Dim2 {

namespace Profile {

bool isProfile(const LineStringD& prof);

size_t indexOfBottomPoint(const LineStringD& prof);

size_t lowerBound(const LineStringD& prof, double x);
size_t upperBound(const LineStringD& prof, double x);

size_t firstSegmentAt(const LineStringD& prof, double x);
size_t lastSegmentAt(const LineStringD& prof, double x);

enum ConflictResolution
{
    PickHighest,
    PickMiddle,
    PickLowest
};

double interpolateY(const LineStringD& prof,
                    double x,
                    ConflictResolution pick = PickMiddle);

bool nearestPointBefore(PointD& nearestPoint,
                        size_t& segment,
                        const LineStringD& prof,
                        const PointD& point);

bool nearestPointAfter(PointD& nearestPoint,
                       size_t& segment,
                       const LineStringD& prof,
                       const PointD& point);

bool firstIntersection(PointD& isect,
                       const LineSegmentD& line,
                       const LineStringD& prof);
}

}}

#endif
