#ifndef JEBMATH_GEOMETRY_PLANARAPROJECTION3_HPP
#define JEBMATH_GEOMETRY_PLANARAPROJECTION3_HPP

#include "../Math/Utilities.hpp"
#include "Plane3.hpp"

namespace JEBMath {

template <typename T>
class PlanarProjection3
{
public:
    PlanarProjection3(const Plane3<T>& plane);
    Vector<T, 2> operator()(const Vector<T, 3>& point);
private:
    Vector<T, 3> m_Unit1;
    Vector<T, 3> m_Unit2;
    double m_Offsets[2];
};

template <typename T>
PlanarProjection3<T> makePlanarProjection(const Plane3<T>& plane);

}

#include "PlanarProjection3-impl.hpp"

#endif
