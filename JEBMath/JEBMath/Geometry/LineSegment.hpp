#ifndef JEB_MATH_LINESEGMENT_HPP
#define JEB_MATH_LINESEGMENT_HPP

#include "Vector.hpp"

namespace JEBMath {

template <typename T, unsigned N>
class LineSegment
{
public:
    LineSegment()
    {}

    LineSegment(const Vector<T, N>& start, const Vector<T, N>& end)
        : m_Start(start),
          m_End(end)
    {}

    const Vector<T, N>& getEnd() const
    {
        return m_End;
    }

    void setEnd(const Vector<T, N>& end)
    {
        m_End = end;
    }

    const Vector<T, N>& getStart() const
    {
        return m_Start;
    }

    void setStart(const Vector<T, N>& start)
    {
        m_Start = start;
    }

    Vector<T, N> getVector() const
    {
        return m_End - m_Start;
    }

    Vector<T, N> getPointAtT(double t) const
    {
        return m_Start + getVector() * t;
    }

    T getXAtT(double t) const
    {
        return m_Start.x() + T((m_End.x() - m_Start.x()) * t);
    }

    T getYAtT(double t) const
    {
        return m_Start.y() + T((m_End.y() - m_Start.y()) * t);
    }
private:
    Vector<T, N> m_Start;
    Vector<T, N> m_End;
};

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const LineSegment<T, N>& line);

template <typename T, unsigned N>
LineSegment<T, N> makeLineSegment(const Vector<T, N>& start,
                                  const Vector<T, N>& end);

template <typename T, unsigned N>
double getLength(const LineSegment<T, N>& line);

template <typename T, unsigned N>
LineSegment<T, N> getReverse(const LineSegment<T, N>& line);

template <typename T, unsigned N>
Vector<T, N> getNearestPoint(const LineSegment<T, N>& line,
                             const Vector<T, N>& point);

template <typename T>
Vector<T, 2> getRelativePosition(const LineSegment<T, 2>& line,
                                 const Vector<T, 2>& point);

}

#include "LineSegment-impl.hpp"

#endif
