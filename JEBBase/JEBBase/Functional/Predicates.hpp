/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_FUNCTIONAL_PREDICATES_HPP
#define JEBBASE_FUNCTIONAL_PREDICATES_HPP

#include <limits>
#include <cmath>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Functional {

/** @brief Returns true if @a value is between @a min and @a max (only
 *  @a min inclusive)
 */
template <typename T>
bool inRange(T value, T min, T max)
{
    return !(value < min) && value < max;
}

inline bool inRange(double value, double min, double max, double epsilon)
{
    return std::fabs(value - min) > -epsilon && std::fabs(max - value) > -epsilon;
}

template <>
inline bool inRange(double value, double min, double max)
{
    return inRange(value, min, max, std::numeric_limits<double>::epsilon());
}

/** @brief Returns true if @a value is between @a min and @a max (both
 *  inclusive)
 */
template <typename T>
bool inRangeI(T value, T min, T max)
{
    return !(value < min) && !(max < value);
}

template <typename T>
bool oneOf(T value, T cand1)
{
    return value == cand1;
}

template <typename T>
bool oneOf(T value, T cand1, T cand2)
{
    return value == cand1 || value == cand2;
}

template <typename T>
bool oneOf(T value, T cand1, T cand2, T cand3)
{
    return oneOf(value, cand1, cand2) || value == cand3;
}

template <typename T>
bool oneOf(T value, T cand1, T cand2, T cand3, T cand4)
{
    return oneOf(value, cand1, cand2) || oneOf(value, cand3, cand4);
}

template <typename T>
bool oneOf(T value, T cand1, T cand2, T cand3, T cand4, T cand5)
{
    return oneOf(value, cand1, cand2, cand3) || oneOf(value, cand4, cand5);
}

}}

#endif
