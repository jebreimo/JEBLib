#ifndef JEB_LIMITS_HPP
#define JEB_LIMITS_HPP

#include <limits>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEB { namespace Limits {

template <typename T>
T min()
{
    return std::numeric_limits<T>::min();
}

template <typename T>
T max()
{
    return std::numeric_limits<T>::max();
}

template <>
inline float min<float>()
{
    return -std::numeric_limits<float>::max();
}

template <>
inline double min<double>()
{
    return -std::numeric_limits<double>::max();
}

}}

#endif
