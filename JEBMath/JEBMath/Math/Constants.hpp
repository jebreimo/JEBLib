#ifndef JEB_MATH_CONSTANTS_HPP
#define JEB_MATH_CONSTANTS_HPP

#include <cfloat>
#include <climits>
#include <cstdint>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

constexpr size_t InvalidIndex = SIZE_MAX;
constexpr double InvalidDouble = -DBL_MAX;
constexpr double DoubleTolerance = 1e-9;

constexpr double Pi = 3.1415926535897932384626433832795;

static inline bool isValid(double v) {return v != InvalidDouble;}
static inline bool isValid(size_t v) {return v != InvalidIndex;}

}

#endif
