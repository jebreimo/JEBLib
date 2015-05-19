#ifndef JEBMATH_GEOMETRY_PROFILE_HPP
#define JEBMATH_GEOMETRY_PROFILE_HPP

// #include "Intersections.hpp"
#include <vector>
#include "LineSegment.hpp"

namespace JEBMath {

typedef std::vector<Vector<double, 2>> Profile;

bool isProfile(const Profile& prof);

size_t indexOfBottomPoint(const Profile& prof);

size_t lowerBound(const Profile& prof, double x);
size_t upperBound(const Profile& prof, double x);

size_t firstSegmentAt(const Profile& prof, double x);
size_t lastSegmentAt(const Profile& prof, double x);

enum ConflictResolution
{
    PickHighest,
    PickMiddle,
    PickLowest
};

double interpolateY(const Profile& prof,
                    double x,
                    ConflictResolution pick = PickMiddle);

bool nearestPointBefore(Vector<double, 2>& nearestPoint,
                        size_t& segment,
                        const Profile& prof,
                        const Vector<double, 2>& point);

bool nearestPointAfter(Vector<double, 2>& nearestPoint,
                       size_t& segment,
                       const Profile& prof,
                       const Vector<double, 2>& point);

bool firstIntersection(Vector<double, 2>& isect,
                       const LineSegment<double, 2>& line,
                       const Profile& prof);

}

#endif
