#ifndef JEB_MATH_LINESTRING_HPP
#define JEB_MATH_LINESTRING_HPP

#include <iosfwd>
#include <vector>
#include "LineSegment.hpp"

namespace JEBMath {

template <typename T, size_t N>
LineSegment<T, N> segment(const std::vector<Point<T, N>>& lineString,
                          size_t i);

template <typename T, size_t N>
LineSegment<T, N> firstSegment(const std::vector<Point<T, N>>& lineString);

template <typename T, size_t N>
LineSegment<T, N> lastSegment(const std::vector<Point<T, N>>& lineString);

template <typename T, size_t N>
void removeSegment(std::vector<Point<T, N>>& lineString, size_t i);

template <typename T, size_t N>
size_t segmentCount(const std::vector<Point<T, N>>& lineString);

template <typename T, size_t N>
std::pair<Point<T, N>, Point<T, N>> boundingBox(
        const std::vector<Point<T, N>>& lineString);

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<Point<T, N>>& ls);

}

#include "LineString.impl.hpp"

#endif
