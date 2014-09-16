#ifndef JEBMATH_GEOMETRY_TYPES_HPP
#define JEBMATH_GEOMETRY_TYPES_HPP

#include "Line.hpp"
#include "LineSegment.hpp"
#include "LineString.hpp"
#include "Plane.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Vector.hpp"

namespace JEBMath {

namespace Dim2 {

typedef Line<double, 2> LineD;
typedef LineSegment<double, 2> LineSegmentD;
typedef std::vector<Point<double, 2>> LineStringD;
typedef std::vector<Point<double, 2>> PolygonD;
typedef Point<double, 2> PointD;
typedef Rect<double> RectD;
typedef Vector<double, 2> VectorD;
inline PointD pointD(double x, double y) {return ::JEBMath::point2(x, y);}
inline VectorD vectorD(double x, double y) {return ::JEBMath::vector2(x, y);}

typedef Line<float, 2> LineF;
typedef LineSegment<float, 2> LineSegmentF;
typedef std::vector<Point<float, 2>> LineStringF;
typedef std::vector<Point<float, 2>> PolygonF;
typedef Point<float, 2> PointF;
typedef Rect<float> RectF;
typedef Vector<float, 2> VectorF;
inline PointF pointF(float x, float y) {return ::JEBMath::point2(x, y);}
inline VectorF vectorF(float x, float y) {return ::JEBMath::vector2(x, y);}

typedef Line<int, 2> LineI;
typedef LineSegment<int, 2> LineSegmentI;
typedef std::vector<Point<int, 2>> LineStringI;
typedef std::vector<Point<int, 2>> PolygonI;
typedef Point<int, 2> PointI;
typedef Rect<int> RectI;
typedef Vector<int, 2> VectorI;
inline PointI pointI(int x, int y) {return ::JEBMath::point2(x, y);}
inline VectorI vectorI(int x, int y) {return ::JEBMath::vector2(x, y);}
}

namespace Dim3 {

typedef Line<double, 3> LineD;
typedef LineSegment<double, 3> LineSegmentD;
typedef std::vector<Point<double, 3>> LineStringD;
typedef Plane3<double> PlaneD;
typedef Point<double, 3> PointD;
typedef Vector<double, 3> VectorD;
inline PointD pointD(double x, double y, double z) {return ::JEBMath::point3(x, y, z);}
inline VectorD vectorD(double x, double y, double z) {return ::JEBMath::vector3(x, y, z);}
}

}

#endif
