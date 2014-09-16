#include "LineSegment.hpp"

namespace JEBMath {

template <typename T, size_t N>
Line<T, N>::Line(const typename Line<T, N>::LineSegment& ls)
    : m_Point(ls.start()),
      m_Vector(ls.vector())
{}

}
