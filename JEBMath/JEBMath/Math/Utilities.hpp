#ifndef JEB_MATH_UTILTIES_HPP
#define JEB_MATH_UTILTIES_HPP

#include <cmath>
#include "Constants.hpp"

namespace JEBMath {

template <typename T>
T sign(T value)
{
    if (value > 0)
        return T(1);
    else if (value < 0)
        return T(-1);
    else
        return T(0);
}

constexpr double radians(double degrees)
{
    return degrees * Pi / 180;
}

constexpr double degrees(double radians)
{
    return radians * 180 / Pi;
}

template <typename T, typename U>
constexpr T nearest(U value)
{
    return T(value);
}

template <typename T>
constexpr T nearest(float value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float nearest<float>(float value)
{
    return value;
}

template <>
constexpr double nearest<double>(float value)
{
    return value;
}

template <>
constexpr long double nearest<long double>(float value)
{
    return value;
}

template <typename T>
constexpr T nearest(double value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float nearest<float>(double value)
{
    return float(value);
}

template <>
constexpr double nearest<double>(double value)
{
    return value;
}

template <>
constexpr long double nearest<long double>(double value)
{
    return value;
}

template <typename T>
constexpr T nearest(long double value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float nearest<float>(long double value)
{
    return float(value);
}

template <>
constexpr double nearest<double>(long double value)
{
    return double(value);
}

template <>
constexpr long double nearest<long double>(long double value)
{
    return value;
}

}

#endif
