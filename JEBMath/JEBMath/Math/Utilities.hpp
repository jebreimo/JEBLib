#ifndef JEBMATH_UTILTIES_HPP
#define JEBMATH_UTILTIES_HPP

#include <cmath>
#include "Constants.hpp"

namespace JEBMath {

inline int compare(double a, double b, double tolerance)
{
  auto d = a - b;
  if (std::fabs(d) < tolerance)
    return 0;
  return d < 0 ? -1 : 1;
}

template <typename T>
T getSign(T value)
{
    if (value > 0)
        return T(1);
    else if (value < 0)
        return T(-1);
    else
        return T(0);
}

constexpr double toRadians(double degrees)
{
    return degrees * Pi / 180;
}

constexpr double toDegrees(double radians)
{
    return radians * 180 / Pi;
}

inline int modulo(int dividend, int divisor)
{
    if (dividend >= 0)
        return dividend % divisor;
    else
        return divisor - (-dividend % divisor);
}

template <typename T>
T getClamped(T value, T min, T max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

template <typename T>
void clamp(T& value, T min, T max)
{
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
}

template <typename T, typename U>
constexpr T getNearest(U value)
{
    return T(value);
}

template <typename T>
constexpr T getNearest(float value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float getNearest<float>(float value)
{
    return value;
}

template <>
constexpr double getNearest<double>(float value)
{
    return value;
}

template <>
constexpr long double getNearest<long double>(float value)
{
    return value;
}

template <typename T>
constexpr T getNearest(double value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float getNearest<float>(double value)
{
    return float(value);
}

template <>
constexpr double getNearest<double>(double value)
{
    return value;
}

template <>
constexpr long double getNearest<long double>(double value)
{
    return value;
}

template <typename T>
constexpr T getNearest(long double value)
{
    // Good enough for integer types. I've seen examples of values very
    // close to *.5 where this rounds up when it should have rounded down and
    // vice versa, but in most use-cases this is unimportant.
    return T(value + 0.5);
}

template <>
constexpr float getNearest<float>(long double value)
{
    return float(value);
}

template <>
constexpr double getNearest<double>(long double value)
{
    return double(value);
}

template <>
constexpr long double getNearest<long double>(long double value)
{
    return value;
}

}

#endif
