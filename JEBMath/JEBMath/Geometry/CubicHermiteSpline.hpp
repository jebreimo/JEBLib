#ifndef JEB_MATH_CUBICHERMITESPLINE_HPP
#define JEB_MATH_CUBICHERMITESPLINE_HPP

#include "../JEBMathDefinitions.hpp"
#include "Vector.hpp"

namespace JEBMath {

/** @brief The Cubic sermite Spline interpolates points using a third degree
 *         polynomial.
 *
 *  Given a start and end point and the tangent vectors in these two points,
 *  the Cubic Hermite spline will compute points along the third degree
 *  polynomial that join these four knowns. The Cubic Hermite spline is
 *  valid for both 2-dimensional and 3-dimensional points and vectors, and
 *  forms the basis for several other splines such as the Cardinal spline.
 *
 *  The formula for computing the interpolated point @a p at @a t
 *  @f[ p(t) = h_{00}(t) \cdot \mbox{point}_{0} +
 *              h_{10}(t) \cdot \mbox{tangent}_{0} +
 *              h_{01}(t) \cdot \mbox{point}_{1} +
 *              h_{11}(t) \cdot \mbox{tangent}_{1}
 *  @f]
 *
 *  and the four Hermite basis functions are:
 *  @f{eqnarray*}{
 *      h_{00}(t) &=& 2t^{3} - 3t^{2} + 1
 *      h_{10}(t) &=& t^{3} - 2t^{2} + t
 *      h_{01}(t) &=& -2t^{3} + 3t^{2}
 *      h_{11}(t) &=& t^{3} - t^{2}
 *  @f}
 */
template <unsigned N>
class CubicHermiteSpline
{
public:
    CubicHermiteSpline();
    CubicHermiteSpline(const Vector<double, N>& start,
                       const Vector<double, N>& startTangent,
                       const Vector<double, N>& end,
                       const Vector<double, N>& endTangent);

    const Vector<double, N>& getStart() const;
    const Vector<double, N>& getStartTangent() const;
    Vector<double, N> getEnd() const;
    Vector<double, N> getEndTangent() const;

    void setPointsAndTangents(const Vector<double, N>& start,
                              const Vector<double, N>& startTangent,
                              const Vector<double, N>& end,
                              const Vector<double, N>& endTangent);

    Vector<double, N> getPointAt(double t) const;
private:
    Vector<double, N> m_Start;
    Vector<double, N> m_StartTangent;
    Vector<double, N> m_A;
    Vector<double, N> m_B;
};

}

#include "CubicHermiteSpline-impl.hpp"

#endif
