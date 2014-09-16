#ifndef JEBMATH_GEOMETRY_ARC_HPP
#define JEBMATH_GEOMETRY_ARC_HPP

#include "Plane.hpp"

namespace JEBMath {

template <typename T>
class Arc<T>
{
public:
    typedef Point<T, 2> Point;

    Arc(const Point& start,
        const Point& center,
        double angle);
private:
    Point m_Start;
    Point m_Center;
    double m_Angle;
};

}

#endif
