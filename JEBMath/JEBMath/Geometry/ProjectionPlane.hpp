#ifndef JEB_MATH_PROJECTIONPLANE_HPP
#define JEB_MATH_PROJECTIONPLANE_HPP

#include "Vector.hpp"

namespace JEBMath {

class ProjectionPlane
{
public:
    typedef Point<double, 2> Point2;
    typedef Point<double, 3> Point3;
    typedef Vector<double, 2> Vector2;
    typedef Vector<double, 3> Vector3;

    ProjectionPlane();
    ProjectionPlane(const Point3& origin,
                    const Vector3& xUnit,
                    const Vector3& yUnit);

    Vector normal() const;

    Point2 project(const Point3& p);
    Vector2 project(const Vector3& v);
    Point3 unproject(const Point2& p);
    Vector3 unproject(const Vector2& v);
private:
    Point m_Origin;
    Vector m_XUnit;
    Vcetor m_YUnit;
};

}

#endif
