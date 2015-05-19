#include "HomogeneousTransforms.hpp"

#include <cmath>
#include "Vector.hpp"

namespace JEBMath { namespace HomogeneousTransforms {

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

Matrix<double, 4> scale4DTrans(double s)
{
    return scale4D(s);
}

Matrix<double, 4> scale4DTrans(const Vector<double, 3>& scales)
{
    return scale4D(scales);
}

Matrix<double, 4> rotateZ4D(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{c, -s, 0, 0,
                             s,  c, 0, 0,
                             0,  0, 1, 0,
                             0,  0, 0, 1};
}

Matrix<double, 4> rotateZ4DTrans(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{ c, -s, 0, 0,
                             -s,  c, 0, 0,
                              0,  0, 1, 0,
                              0,  0, 0, 1};
}

Matrix<double, 4> rotateY4D(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{ c, 0, s, 0,
                              0, 1, 0, 0,
                             -s, 0, c, 0,
                              0, 0, 0, 1};
}

Matrix<double, 4> rotateY4DTrans(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{c, 0, -s, 0,
                             0, 1,  0, 0,
                             s, 0,  c, 0,
                             0, 0,  0, 1};
}

Matrix<double, 4> rotateX4D(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{1,  0, 0, 0,
                             0,  c, s, 0,
                             0, -s, c, 0,
                             0,  0, 0, 1};
}

Matrix<double, 4> rotateX4DTrans(double angle)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    return Matrix<double, 4>{1, 0,  0, 0,
                             0, c, -s, 0,
                             0, s,  c, 0,
                             0, 0,  0, 1};
}

Matrix<double, 4> rotate4D(double angle, const Vector<double, 3>& axis)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    auto cx = axis * ((1 - c) * axis[0]);
    auto cy = axis * ((1 - c) * axis[1]);
    auto cz = axis * ((1 - c) * axis[2]);
    auto sa = s * axis;
    return Matrix<double, 4>{cx[0] + c,     cx[1] - sa[2], cx[2] + sa[1], 0,
                             cy[0] + sa[2], cy[1] + c,     cy[2] - sa[0], 0,
                             cz[0] - sa[1], cz[1] + sa[0], cz[2] + c,     0,
                                         0,             0,         0,     1};
}

Matrix<double, 4> rotate4DTrans(double angle,
                                const Vector<double, 3>& axis)
{
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    auto cx = axis * ((1 - c) * axis[0]);
    auto cy = axis * ((1 - c) * axis[1]);
    auto cz = axis * ((1 - c) * axis[2]);
    auto sa = s * axis;
    return Matrix<double, 4>{cx[0] + c,     cy[0] + sa[2], cz[0] - sa[1], 0,
                             cx[1] - sa[2], cy[1] + c,     cz[1] + sa[0], 0,
                             cx[2] + sa[1], cy[2] - sa[0], cz[2] + c,     0,
                                         0,             0,         0,     1};
}

Matrix<double, 4> translate4D(double x, double y, double z)
{
    return Matrix<double, 4>{0, 0, 0, x,
                             0, 0, 0, y,
                             0, 0, 0, z,
                             0, 0, 0, 1};
}

Matrix<double, 4> translate4DTrans(double x, double y, double z)
{
    return Matrix<double, 4>{0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             x, y, z, 1};
}

}}
