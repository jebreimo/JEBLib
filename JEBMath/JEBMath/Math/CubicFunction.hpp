#ifndef JEBMATH_MATH_CUBICFUNCTION_HPP
#define JEBMATH_MATH_CUBICFUNCTION_HPP

#include <complex>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

/** @brief A cubic function is a third degree polynomial.
 *
 * The cubic function is defined by four parameters @a a, @a b, @a c and @a
 * d, it's value at @a t is a * t**3 + b * t**2 + c * t + d.
 */
class CubicFunction
{
public:
    typedef std::complex<double> Complex;

    CubicFunction();
    CubicFunction(double a, double b, double c, double d);

    double a() const;
    void setA(double a);

    double b() const;
    void setB(double b);

    double c() const;
    void setC(double c);

    double d() const;
    void setD(double d);

    /** @brief Returns the value of the cubic function at @a t.
     */
    double value(double t) const;

    /** @brief Returns complex root @a n (@a n is 0, 1 or 2).
     *
     *  This is intended for optimizing when only one root value is needed,
     *  and which one it is, is known.
     */
    Complex root(size_t n) const;

    /** @brief Returns real root @a n (@a n is 0, 1 or 2).
     *
     *  This is intended for optimizing when only one root value is needed,
     *  and which one it is, is known.
     *
     *  @return @a true if root @n is real, @a false if it's complex.
     */
    bool root(size_t n, double& t) const;

    /** @brief Compute all real roots.
     *
     *  @return The number of unique real roots (1, 2 or 3).
     */
    size_t roots(double (&t)[3]) const;

    /** @brief Compute all three complex roots.
     */
    void roots(Complex& t1, Complex& t2, Complex& t3) const;

    /** @brief Returns the maximum acceptable range for floating point
     *         errors.
     *
     *  The floating point calculations performed when calculating the roots
     *  introduces some error, the size of which depends on the sizes of @a
     *  a, @a b, @a c and @a d. This affects in particular the computation of
     *  the real roots, where roots with an imaginary value different from 0
     *  should be ignored.
     */
    static double epsilon();

    /** @brief Set the maximum acceptable range for floating point errors.
     */
    static void setEpsilon(double epsilon);
private:
    double factor1() const;
    static Complex factor2();
    static Complex factor3();
    void cubicRoots(Complex& root1, Complex& root2) const;

    double m_A;
    double m_B;
    double m_C;
    double m_D;
    static double s_Epsilon;
};

}

#endif
