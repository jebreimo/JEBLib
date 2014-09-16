#include "CubicFunction.hpp"
#include <cmath>

namespace JEBMath {

using namespace std;

double CubicFunction::s_Epsilon = 1e-12;

CubicFunction::CubicFunction()
    : m_A(0),
      m_B(0),
      m_C(0),
      m_D(0)
{
}

CubicFunction::CubicFunction(double a, double b, double c, double d)
    : m_A(a),
      m_B(b),
      m_C(c),
      m_D(d)
{
}

double CubicFunction::a() const
{
    return m_A;
}

void CubicFunction::setA(double a)
{
    m_A = a;
}

double CubicFunction::b() const
{
    return m_B;
}

void CubicFunction::setB(double b)
{
    m_B = b;
}

double CubicFunction::c() const
{
    return m_C;
}

void CubicFunction::setC(double c)
{
    m_C = c;
}

double CubicFunction::d() const
{
    return m_D;
}

void CubicFunction::setD(double d)
{
    m_D = d;
}

double CubicFunction::value(double t) const
{
    return ((t * m_A + m_B) * t + m_C) * t + m_D;
}

size_t CubicFunction::roots(double (&t)[3]) const
{
    Complex t1, t2, t3;
    roots(t1, t2, t3);
    size_t i = 0;
    if (fabs(t1.imag()) <= s_Epsilon)
        t[i++] = t1.real();
    if (fabs(t2.imag()) <= s_Epsilon &&
            (i == 0 || fabs(t2.real() - t[i - 1]) >= s_Epsilon))
        t[i++] = t2.real();
    if (fabs(t3.imag()) <= s_Epsilon &&
            (i == 0 || fabs(t3.real() - t[i - 1]) >= s_Epsilon))
        t[i++] = t3.real();
    return i;
}

void CubicFunction::roots(Complex& t1, Complex& t2, Complex& t3) const
{
    Complex root1, root2;
    cubicRoots(root1, root2);
    double f = factor1();
    Complex g = factor2();
    Complex h = factor3();
    t1 = -f * (m_B + root1 + root2);
    t2 = -f * (m_B - g * root1 - h * root2);
    t3 = -f * (m_B - h * root1 - g * root2);
}

CubicFunction::Complex CubicFunction::root(size_t n) const
{
    Complex root1, root2;
    cubicRoots(root1, root2);
    double f = factor1();
    Complex g = factor2();
    Complex h = factor3();
    switch (n)
    {
    case 0:
        return -f * (m_B + root1 + root2);
    case 1:
        return -f * (m_B - g * root1 - h * root2);
    case 2:
        return -f * (m_B - h * root1 - g * root2);
    default:
        return Complex();
    }
}

bool CubicFunction::root(size_t n, double& t) const
{
    Complex c = root(n);
    if (fabs(c.imag()) > s_Epsilon)
        return false;

    t = c.real();
    return true;
}

double CubicFunction::epsilon()
{
    return s_Epsilon;
}

void CubicFunction::setEpsilon(double epsilon)
{
    s_Epsilon = epsilon;
}

double CubicFunction::factor1() const
{
    return 1.0 / (3 * m_A);
}

CubicFunction::Complex CubicFunction::factor2()
{
    return (1.0 + Complex(0, 1) * sqrt(3.0)) / 2.0;
}

CubicFunction::Complex CubicFunction::factor3()
{
    return (1.0 - Complex(0, 1) * sqrt(3.0)) / 2.0;
}

void CubicFunction::cubicRoots(Complex& root1, Complex& root2) const
{
    double r1 = 2 * pow(m_B, 3) - 9 * m_A * m_B * m_C + 27 * m_A * m_A * m_D;
    double r2 = 4 * pow(m_B * m_B - 3 * m_A * m_C, 3);
    Complex c1(r1, 0), c2(r2, 0);
    Complex innerRoot = sqrt(c1 * c1 - c2);
    root1 = pow(0.5 * (c1 + innerRoot), 1.0 / 3.0);
    root2 = pow(0.5 * (c1 - innerRoot), 1.0 / 3.0);
}

}
