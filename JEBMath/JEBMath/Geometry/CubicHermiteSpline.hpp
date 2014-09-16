#ifndef JEB_MATH_CUBICHERMITESPLINE_HPP
#define JEB_MATH_CUBICHERMITESPLINE_HPP

#include "JEBMath/JEBMathDefinitions.hpp"

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
template <typename Point, typename Vector>
class CubicHermiteSpline
{
public:
    CubicHermiteSpline();
    CubicHermiteSpline(const Point& start, const Vector& startTangent,
                       const Point& end, const Vector& endTangent);

    const Point& start() const;
    const Vector& startTangent() const;
    Point end() const;
    Vector endTangent() const;

    void set(const Point& start, const Vector& startTangent,
             const Point& end, const Vector& endTangent);

    Point pointAt(double t) const;
private:
    Point m_Start;
    Vector m_StartTangent;
    Vector m_A;
    Vector m_B;
};

}

#include "CubicHermiteSpline.impl.hpp"

#endif
