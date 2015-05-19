#ifndef JEB_MATH_LINESTRING_HPP
#define JEB_MATH_LINESTRING_HPP

#include <iosfwd>
#include <vector>
#include "LineSegment.hpp"

namespace JEBMath {

template <typename T, unsigned N>
LineSegment<T, N> getSegment(const std::vector<Vector<T, N>>& lineString,
                             size_t i);

template <typename T, unsigned N>
LineSegment<T, N> getFirstSegment(
        const std::vector<Vector<T, N>>& lineString);

template <typename T, unsigned N>
LineSegment<T, N> getLastSegment(
        const std::vector<Vector<T, N>>& lineString);

template <typename T, unsigned N>
void removeSegment(std::vector<Vector<T, N>>& lineString, size_t i);

template <typename T, unsigned N>
size_t getSegmentCount(const std::vector<Vector<T, N>>& lineString);

template <typename T, unsigned N>
std::pair<Vector<T, N>, Vector<T, N>> getBoundingBox(
        const std::vector<Vector<T, N>>& lineString);

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<Vector<T, N>>& ls);

}

#include "LineString-impl.hpp"

#endif
