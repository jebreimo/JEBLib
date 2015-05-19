#ifndef JEBMATH_GEOMETRY_DISTANCE_HPP
#define JEBMATH_GEOMETRY_DISTANCE_HPP

#include "Line.hpp"
#include "LineString.hpp"

namespace JEBMath {

template <typename T, typename U, unsigned N>
double getDistance(const Vector<T, N>& a, const Vector<U, N>& b);

template <typename T, typename U>
double getDistance(const Line<T, 2>& l, const Vector<U, 2>& p);

template <typename T, typename U>
double getDistance(const Vector<T, 2>& p, const Line<U, 2>& l);

template <typename T, typename U>
double getDistance(const LineSegment<T, 2>& ls, const Vector<U, 2>& p);

template <typename T, typename U>
double getDistance(const Vector<T, 2>& p, const LineSegment<U, 2>& ls);

}

#include "Distance-impl.hpp"

#endif
