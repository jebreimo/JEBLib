#ifndef JEBMATH_GEOMETRY_HOMOGENEOUSTRANSFORMS_HPP
#define JEBMATH_GEOMETRY_HOMOGENEOUSTRANSFORMS_HPP

namespace JEBMath { namespace HomogeneousTransforms {

Matrix<double, 4> scale4D(double s);
Matrix<double, 4> scale4D(const Vector<double, 3>& scales);
Matrix<double, 4> scale4DTrans(double s);
Matrix<double, 4> scale4DTrans(const Vector<double, 3>& scales);
Matrix<double, 4> rotateZ4D(double angle);
Matrix<double, 4> rotateZ4DTrans(double angle);
Matrix<double, 4> rotateY4D(double angle);
Matrix<double, 4> rotateY4DTrans(double angle);
Matrix<double, 4> rotateX4D(double angle);
Matrix<double, 4> rotateX4DTrans(double angle);
Matrix<double, 4> rotate4D(double angle, const Vector<double, 3>& axis);
Matrix<double, 4> rotate4DTrans(double angle, const Vector<double, 3>& axis);
Matrix<double, 4> translate4D(double x, double y, double z);
Matrix<double, 4> translate4DTrans(double x, double y, double z);

}}

#endif
