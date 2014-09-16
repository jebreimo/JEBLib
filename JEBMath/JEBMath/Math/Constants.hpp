#ifndef JEB_MATH_CONSTANTS_HPP
#define JEB_MATH_CONSTANTS_HPP

#include <limits>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

constexpr size_t InvalidIndex = std::numeric_limits<size_t>::max();
constexpr double InvalidDouble = -std::numeric_limits<double>::max();
constexpr double DoubleTolerance = 1e-9;

constexpr double Pi = 3.1415926535897932384626433832795;

static inline bool isValid(double v) {return v != InvalidDouble;}
static inline bool isValid(size_t v) {return v != InvalidIndex;}

}

#endif
