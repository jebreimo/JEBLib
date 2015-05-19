#ifndef JEBMATH_GEOMETRY_ROTATEDRECT_HPP
#define JEBMATH_GEOMETRY_ROTATEDRECT_HPP

#include <cmath>
#include "Rect.hpp"
#include "LineString.hpp"

namespace JEBMath {

class RotatedRect
{
public:
    RotatedRect()
        : m_Angle(0)
    {}

    template <typename T, typename U>
    RotatedRect(const Vector<T, 2>& origin,
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

    Vector<double, 2> getCenter() const
    {
        return m_Origin + getRotated(m_Size / 2, m_Angle);
    }

    void setCenter(const Vector<double, 2>& center)
    {
        m_Origin = center - getRotated(m_Size / 2, m_Angle);
    }

    const Vector<double, 2>& getOrigin() const
    {
        return m_Origin;
    }

    void setOrigin(const Vector<double, 2>& origin)
    {
        m_Origin = origin;
    }

    const Vector<double, 2>& getSize() const
    {
        return m_Size;
    }

    void setSize(const Vector<double, 2>& size)
    {
        m_Size = size;
    }

    double getAngle() const
    {
        return m_Angle;
    }

    void setAngle(double angle)
    {
        m_Angle = angle;
    }

    Vector<double, 2> getPoint(size_t n) const
    {
        switch (n & 0x3)
        {
        case 0:
            return m_Origin;
        case 1:
            return m_Origin + getRotated(vector2(getX(m_Size), 0.0), m_Angle);
        case 2:
            return m_Origin + getRotated(m_Size, m_Angle);
        case 3:
            return m_Origin + getRotated(vector2(0.0, getY(m_Size)), m_Angle);
        default:
            return Vector<double, 2>{};
        }
    }

    std::vector<Vector<double, 2>> getPoints() const
    {
        auto c = std::cos(m_Angle);
        auto s = std::sin(m_Angle);
        auto xw = getX(m_Size) * c, xh = getX(m_Size) * s;
        auto yw = getY(m_Size) * s, yh = getY(m_Size) * c;
        return std::vector<Vector<double, 2>>{
                m_Origin,
                m_Origin + vector2(xw, xh),
                m_Origin + vector2(xw - yw, xh + yh),
                m_Origin + vector2(-yw, yh)
                };
    }

    void rotate(const Vector<double, 2>& point, double angle)
    {
        m_Angle += angle;
        m_Origin = point + getRotated(m_Origin - point, angle);
    }

    void rotateCenter(double angle)
    {
        rotate(getCenter(), angle);
    }
private:
    Vector<double, 2> m_Origin;
    Vector<double, 2> m_Size;
    double m_Angle;
};

inline std::pair<Vector<double, 2>, Vector<double, 2>> getBoundingBox(
        const RotatedRect& rect)
{
    return getBoundingBox(rect.getPoints());
}

inline std::ostream& operator<<(std::ostream& os, const RotatedRect& r)
{
    return os << "{\"origin\":" << r.getOrigin()
              << ", \"size\":" << r.getSize()
              << ", \"angle\":" << r.getAngle() << "}";
}

}

#endif
