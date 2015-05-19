#ifndef JEBMATH_GEOMETRY_LINE_HPP
#define JEBMATH_GEOMETRY_LINE_HPP

#include "Vector.hpp"

namespace JEBMath {

template <typename T, unsigned N>
class LineSegment;

template <typename T, unsigned N>
class Line
{
public:
    Line()
    {}

    template <typename U>
    explicit Line(const LineSegment<U, N>& ls)
        : m_Point(ls.getStart()),
          m_Vector(ls.getVector())
    {}

    Line(const Vector<T, N>& point, const Vector<T, N>& vector)
        : m_Point(point),
          m_Vector(vector)
    {}

    const Vector<T, N>& getPoint() const {return m_Point;}
    void setPoint(const Vector<T, N>& point)
    {
        m_Point = point;
    }

    const Vector<T, N>& getVector() const {return m_Vector;}
    void setVector(const Vector<T, N>& vector)
    {
        m_Vector = vector;
    }
private:
    Vector<T, N> m_Point;
    Vector<T, N> m_Vector;
};


template <typename T, unsigned N>
Line<T, N> makeLine(const Vector<T, N>& point,
                    const Vector<T, N>& vector)
{
    return Line<T, N>(point, vector);
}

}

#endif
