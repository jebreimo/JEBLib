#ifndef JEB_MATH_FRESNELINTEGRALS_HPP
#define JEB_MATH_FRESNELINTEGRALS_HPP

#include <cmath>
#include <utility>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

/** @brief Returns C(t) (the cosine if this is a clothoid).
 */
double fresnelC(double t, size_t order);

/** @brief Returns S(t) (the sine if this is a clothoid).
 */
double fresnelS(double t, size_t order);

/** @brief Returns C(t) and S(t) (the cosine and sine if this is a clothoid).
 *
 *  It's faster to call this function than fresnelC and fresnelS separately.
 */
std::pair<double, double> fresnelCS(double t, size_t order);

}

#endif
