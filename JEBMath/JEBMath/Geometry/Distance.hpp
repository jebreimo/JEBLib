#ifndef JEB_MATH_DISTANCE_HPP
#define JEB_MATH_DISTANCE_HPP

#include "Line.hpp"
#include "LineString.hpp"
#include "Point.hpp"

namespace JEBMath {

template <typename T, typename U, size_t N>
double distance(const Point<T, N>& a, const Point<U, N>& b);

template <typename T, typename U>
double distance(const Line<T, 2>& l, const Point<U, 2>& p);

template <typename T, typename U>
double distance(const Point<T, 2>& p, const Line<U, 2>& l);

template <typename T, typename U>
double distance(const LineSegment<T, 2>& ls, const Point<U, 2>& p);

template <typename T, typename U>
double distance(const Point<T, 2>& p, const LineSegment<U, 2>& ls);

}

#include "Distance.impl.hpp"

#endif
