#ifndef JEB_MATH_PLANE_HPP
#define JEB_MATH_PLANE_HPP

#include "JEBMath/Math/Utilities.hpp"
#include "Vector.hpp"

namespace JEBMath {

template <typename T>
class Plane3
{
public:
    typedef Point<T, 3> Point;
    typedef Vector<T, 3> Vector;

    Plane3();
    Plane3(const Point& origin, const Vector& normal);

    /** @brief Creates orthogonal unit vectors for the plane.
     */
    bool getUnitVectors(Vector& unit1, Vector& unit2) const;

    const Point& orgin() const;
    void setOrgin(const Point& orgin);

    const Vector& normal() const;
    void setNormal(const Vector& normal);
private:
    Point m_Origin;
    Vector m_Normal;
};

template <typename T>
Plane3<T>::Plane3()
{}

template <typename T>
Plane3<T>::Plane3(const Point& origin, const Vector& normal)
    : m_Origin(origin),
      m_Normal(normal)
{}

template <typename T>
bool Plane3<T>::getUnitVectors(Vector& unit1, Vector& unit2) const
{
    if (x(m_Normal) != 0 || y(m_Normal) != 0)
        setXYZ<T>(unit1, -y(m_Normal), x(m_Normal), 0);
    else if (z(m_Normal) != 0)
        setXYZ<T>(unit1, z(m_Normal), 0, 0);
    else
        return false;

    unit1 = unit(unit1);
    unit2 = unit(cross(m_Normal, unit1));
    return true;
}

template <typename T>
const typename Plane3<T>::Point& Plane3<T>::orgin() const
{
    return m_Origin;
}

template <typename T>
void Plane3<T>::setOrgin(const Point& orgin)
{
    m_Origin = orgin;
}

template <typename T>
const typename Plane3<T>::Vector& Plane3<T>::normal() const
{
    return m_Normal;
}

template <typename T>
void Plane3<T>::setNormal(const Vector& normal)
{
    m_Normal = normal;
}

template <typename T>
class PlanarProjection
{
public:
    PlanarProjection(const Plane3<T>& plane);
    Point<T, 2> operator()(const Point<T, 3>& point);
private:
    Vector<T, 3> m_Unit1;
    Vector<T, 3> m_Unit2;
    double m_Offsets[2];
};

template <typename T>
PlanarProjection<T>::PlanarProjection(const Plane3<T>& plane)
{
    plane.getUnitVectors(m_Unit1, m_Unit2);
    m_Offsets[0] = dot(m_Unit1, Vector<T, 3>(plane.origin()));
    m_Offsets[1] = dot(m_Unit2, Vector<T, 3>(plane.origin()));
}

template <typename T>
Point<T, 2> PlanarProjection<T>::operator()(const Point<T, 3>& point)
{
    return point2(m_Unit1 * Vector<T, 3>(point) - m_Offsets[0],
                  m_Unit2 * Vector<T, 3>(point) - m_Offsets[1]);
}

}

#endif
