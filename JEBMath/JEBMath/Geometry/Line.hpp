#ifndef JEB_MATH_LINE_HPP
#define JEB_MATH_LINE_HPP

#include "Point.hpp"
#include "Vector.hpp"

namespace JEBMath {

template <typename T, size_t N>
class LineSegment;

template <typename T, size_t N>
class Line
{
public:
    typedef Point<T, N> Point;
    typedef Vector<T, N> Vector;
    typedef LineSegment<T, N> LineSegment;

    Line() {}
    explicit Line(const LineSegment& ls);
    Line(const Point& p, const Vector& v) : m_Point(p), m_Vector(v) {}

    const Point& point() const {return m_Point;}
    void setPoint(const Point& point) {m_Point = point;}

    const Vector& vector() const {return m_Vector;}
    void setVector(const Vector& vector) {m_Vector = vector;}
private:
    Point m_Point;
    Vector m_Vector;
};

}

#include "Line.impl.hpp"

#endif

