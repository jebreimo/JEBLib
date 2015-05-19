#ifndef JEBMATH_GEOMETRY_PLANE3_HPP
#define JEBMATH_GEOMETRY_PLANE3_HPP

#include "../Math/Utilities.hpp"
#include "Vector.hpp"

namespace JEBMath {

template <typename T>
class Plane3
{
public:
    Plane3();
    Plane3(const Vector<T, 3>& origin, const Vector<T, 3>& normal);

    /** @brief Creates orthogonal unit vectors for the plane.
     */
    bool getUnitVectors(Vector<T, 3>& unit1, Vector<T, 3>& unit2) const;

    const Vector<T, 3>& getOrgin() const;
    void setOrgin(const Vector<T, 3>& orgin);

    const Vector<T, 3>& getNormal() const;
    void setNormal(const Vector<T, 3>& normal);
private:
    Vector<T, 3> m_Origin;
    Vector<T, 3> m_Normal;
};

}

#include "Plane3-impl.hpp"

#endif
