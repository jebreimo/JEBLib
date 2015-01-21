#include "TransposedMatrix.hpp"
#include "Vector.hpp"

namespace JEBMath {

Matrix<double, 4> scale4D(double s);
Matrix<double, 4> scale4D(Vector<double, 3>& scales);

TransposedMatrix<double, 4> scale4DT(double s);
TransposedMatrix<double, 4> scale4DT(Vector<double, 3>& scales);

Matrix<double, 4> rotateZ4D(double angle);
TransposedMatrix<double, 4> rotateZ4DT(double angle);

Matrix<double, 4> rotateY4D(double angle);
TransposedMatrix<double, 4> rotateY4DT(double angle);

Matrix<double, 4> rotateX4D(double angle);
TransposedMatrix<double, 4> rotateX4DT(double angle);

Matrix<double, 4> rotate4D(double angle, const Vector<double, 3>& axis);
TransposedMatrix<double, 4> rotate4DT(double angle,
                                       const Vector<double, 3>& axis);

Matrix<double, 4> translate4D(double x, double y, double z);
TransposedMatrix<double, 4> translate4DT(double x, double y, double z);

}
