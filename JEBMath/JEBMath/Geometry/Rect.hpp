#ifndef JEBMATH_GEOMETRY_RECT_HPP
#define JEBMATH_GEOMETRY_RECT_HPP

#include <vector>
#include "Point.hpp"

namespace JEBMath { namespace Dim2 {

template <typename T>
class Rect
{
public:
    Rect() {}
    Rect(const Point<T, 2>& origin, const Vector<T, 2>& size)
        : m_Origin(origin), m_Size(size) {}

    Point<T, 2> center() const
    {
        return m_Origin + m_Size / 2;
    }

    void setCenter(const Point<T, 2>& center)
    {
        m_Origin = center - m_Size / 2;
    }

    const Point<T, 2>& origin() const
    {
        return m_Origin;
    }

    void setOrigin(const Point<T, 2>& origin)
    {
        m_Origin = origin;
    }

    const Vector<T, 2>& size() const
    {
        return m_Size;
    }

    void setSize(const Vector<T, 2>& size)
    {
        m_Size = size;
    }

    /** @brief Returns the the @a nth vertex of the rectangle.
      *
      * Vertexes are listed in counter-clockwise order if the width
      * and height are both positive.
      *
      * @param n the vertex index, must be in the range 0..3
      */
    Point<T, 2> point(size_t n) const
    {
        switch (n & 0x3)
        {
        case 0: return m_Origin;
        case 1: return m_Origin + vector2(x(m_Size), T{0});
        case 2: return m_Origin + m_Size;
        case 3: return m_Origin + vector2(T{0}, y(m_Size));
        default: return Point<T, 2>{};
        }
    }

    std::vector<Point<T, 2>> points() const
    {
        return std::vector<Point<T, 2>>{
                m_Origin,
                m_Origin, vector2(x(m_Size), T{0}),
                m_Origin + m_Size,
                m_Origin + vector2(T{0}, y(m_Size))
                };
    }
private:
    Point<T, 2> m_Origin;
    Vector<T, 2> m_Size;
};

}}

#endif
