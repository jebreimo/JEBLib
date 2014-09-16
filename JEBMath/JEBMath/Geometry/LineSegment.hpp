#ifndef JEB_MATH_LINESEGMENT_HPP
#define JEB_MATH_LINESEGMENT_HPP

#include "Point.hpp"
#include "Vector.hpp"

namespace JEBMath {

template <typename T, size_t N>
class LineSegment
{
public:
    typedef T value_type;
    typedef Point<T, N> Point;
    typedef Vector<T, N> Vector;

    LineSegment() {}
    LineSegment(const Point& start, const Point& end) : m_Start(start), m_End(end) {}

    const Point& end() const {return m_End;}
    void setEnd(const Point& end) {m_End = end;}

    const Point& start() const {return m_Start;}
    void setStart(const Point& start) {m_Start = start;}

    Vector vector() const {return m_End - m_Start;}
    Point pointAtT(double t) const {return translate(m_Start, vector() * t);}
    T xAtT(double t) const {return m_Start.x() + static_cast<T>((m_End.x() - m_Start.x()) * t);}
    T yAtT(double t) const {return m_Start.y() + static_cast<T>((m_End.y() - m_Start.y()) * t);}
private:
    Point m_Start;
    Point m_End;
};

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const LineSegment<T, N>& ls);

template <typename T, size_t N>
LineSegment<T, N> lineSegment(const Point<T, N>& start, const Point<T, N>& end);

template <typename T, size_t N>
double length(const LineSegment<T, N>& ls);

template <typename T, size_t N>
LineSegment<T, N> reverse(const LineSegment<T, N>& seg);

template <typename T, size_t N>
Point<T, N> nearestPoint(const LineSegment<T, N>& ls, const Point<T, N>& p);

template <typename T>
Point<T, 2> relativePosition(const LineSegment<T, 2>& ls, const Point<T, 2>& p);

}

#include "LineSegment.impl.hpp"

#endif
