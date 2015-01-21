#include "Transforms.hpp"

namespace JEBMath {

Matrix<double, 4> scale4D(double s)
{
    return Matrix<double, 4>{s, 0, 0, 0,
                             0, s, 0, 0,
                             0, 0, s, 0,
                             0, 0, 0, 1};
}

Matrix<double, 4> scale4D(const Vector<double, 3>& scales)
{
    return Matrix<double, 4>{scales[0], 0, 0, 0,
                             0, scales[1], 0, 0,
                             0, 0, scales[2], 0,
                             0, 0, 0, 1};
}

TransposedMatrix<double, 4> scale4DT(double s)
{
    return TransposedMatrix<double, 4>(scale4DT(s));
}

TransposedMatrix<double, 4> scale4DT(const Vector<double, 3>& scales)
{
    return TransposedMatrix<double, 4>(scale4DT(scales));
}

Matrix<double, 4> rotateZ4D(double angle);
TransposedMatrix<double, 4> rotateZ4DT(double angle);

Matrix<double, 4> rotateY4D(double angle);
TransposedMatrix<double, 4> rotateY4DT(double angle);

Matrix<double, 4> rotateX4D(double angle);
TransposedMatrix<double, 4> rotateX4DT(double angle);

Matrix<double, 4> rotate4D(double angle, const Vector<double, 3>& axis);
TransposedMatrix<double, 4> rotate4DT(double angle,
                                       const Vector<double, 3>& axis);

Matrix<double, 4> translate4D(double x, double y, double z)
{
    return Matrix<double, 4>{0, 0, 0, x,
                             0, 0, 0, y,
                             0, 0, 0, z,
                             0, 0, 0, 1};
}

TransposedMatrix<double, 4> translate4DT(double x, double y, double z)
{
    return TransposedMatrix<double, 4>{0, 0, 0, 0,
                                       0, 0, 0, 0,
                                       0, 0, 0, 0,
                                       x, y, z, 1};
}

}
