#ifndef JEBMATH_GEOMETRY_ROTATEDRECT_HPP
#define JEBMATH_GEOMETRY_ROTATEDRECT_HPP

#include <cmath>
#include "Rect.hpp"
#include "LineString.hpp"

#include <JEBDebug/Debug.hpp>

namespace JEBMath { namespace Dim2 {

class RotatedRect
{
public:
    RotatedRect() : m_Angle(0) {}

    template <typename T, typename U>
    RotatedRect(const Point<T, 2>& origin,
                const Vector<U, 2>& size,
                double angle = 0.0)
        : m_Origin(origin),
          m_Size(size),
          m_Angle(angle)
    {}

    template <typename U>
    RotatedRect(const Rect<U>& rect, double angle)
        : m_Origin(rect.origin()),
          m_Size(rect.size()),
          m_Angle(0)
    {}

    Point<double, 2> center() const
    {
        using JEBMath::rotate;
        return m_Origin + rotate(m_Size / 2, m_Angle);
    }

    void setCenter(const Point<double, 2>& center)
    {
        using JEBMath::rotate;
        m_Origin = center - rotate(m_Size / 2, m_Angle);
    }

    const Point<double, 2>& origin() const
    {
        return m_Origin;
    }

    void setOrigin(const Point<double, 2>& origin)
    {
        m_Origin = origin;
    }

    const Vector<double, 2>& size() const
    {
        return m_Size;
    }

    void setSize(const Vector<double, 2>& size)
    {
        m_Size = size;
    }

    double angle() const
    {
        return m_Angle;
    }

    void setAngle(double angle)
    {
        m_Angle = angle;
    }

    Point<double, 2> point(size_t n) const
    {
        using JEBMath::rotate;
        switch (n & 0x3)
        {
        case 0: return m_Origin;
        case 1: return m_Origin + rotate(vector2(x(m_Size), 0.0), m_Angle);
        case 2: return m_Origin + rotate(m_Size, m_Angle);
        case 3: return m_Origin + rotate(vector2(0.0, y(m_Size)), m_Angle);
        default: return Point<double, 2>{};
        }
    }

    std::vector<Point<double, 2>> points() const
    {
        auto c = std::cos(m_Angle);
        auto s = std::sin(m_Angle);
        auto xw = x(m_Size) * c, xh = x(m_Size) * s;
        auto yw = y(m_Size) * s, yh = y(m_Size) * c;
        return std::vector<Point<double, 2>>{
                m_Origin,
                m_Origin + vector2(xw, xh),
                m_Origin + vector2(xw - yw, xh + yh),
                m_Origin + vector2(-yw, yh)
                };
    }

    void rotate(const Point<double, 2>& point, double angle)
    {
        using JEBMath::rotate;
        m_Angle += angle;
        m_Origin = point + rotate(m_Origin - point, angle);
    }

    void rotateCenter(double angle)
    {
        rotate(center(), angle);
    }
private:
    Point<double, 2> m_Origin;
    Vector<double, 2> m_Size;
    double m_Angle;
};

inline std::pair<Point<double, 2>, Point<double, 2>> boundingBox(
        const RotatedRect& rect)
{
    return boundingBox(rect.points());
}

inline std::ostream& operator<<(std::ostream& os, const RotatedRect& r)
{
    return os << "[" << r.origin() << " " << r.size()
              << " " << r.angle() << "]";
}

}}

#endif
