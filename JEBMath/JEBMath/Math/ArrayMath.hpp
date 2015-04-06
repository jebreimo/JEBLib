#ifndef JEB_ARRAYMATH_HPP
#define JEB_ARRAYMATH_HPP

#include <cstddef>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath { namespace ArrayMath {

template <typename T, size_t N>
void add(T (&lhs)[N], const T (&rhs)[N])
{
    for (size_t i = 0; i < N; i++)
        lhs[i] += rhs[i];
}

template <typename T, size_t N>
void multiply(T (&lhs)[N], const T (&rhs)[N])
{
    for (size_t i = 0; i < N; i++)
        lhs[i] *= rhs[i];
}

template <typename T, typename U, size_t N>
void multiply(T (&lhs)[N], U rhs)
{
    for (size_t i = 0; i < N; i++)
        lhs[i] = static_cast<T>(lhs[i] * rhs);
}

template <typename T, size_t N>
void subtract(T (&lhs)[N], const T (&rhs)[N])
{
    for (size_t i = 0; i < N; i++)
        lhs[i] -= rhs[i];
}

/** @defgroup ArrayMath_spec Template specializations for improved performance
  * @{
  */

template <typename T>
void add(T (&lhs)[3], const T (&rhs)[3])
{
    lhs[0] += rhs[0];
    lhs[1] += rhs[1];
    lhs[2] += rhs[2];
}

template <typename T>
void add(T (&lhs)[4], const T (&rhs)[4])
{
    lhs[0] += rhs[0];
    lhs[1] += rhs[1];
    lhs[2] += rhs[2];
    lhs[3] += rhs[3];
}

template <typename T>
void multiply(T (&lhs)[3], const T (&rhs)[3])
{
    lhs[0] *= rhs[0];
    lhs[1] *= rhs[1];
    lhs[2] *= rhs[2];
}

template <typename T>
void multiply(T (&lhs)[4], const T (&rhs)[4])
{
    lhs[0] *= rhs[0];
    lhs[1] *= rhs[1];
    lhs[2] *= rhs[2];
    lhs[3] *= rhs[3];
}

template <typename T, typename U>
void multiply(T (&lhs)[3], U rhs)
{
    lhs[0] = static_cast<T>(lhs[0] * rhs);
    lhs[1] = static_cast<T>(lhs[1] * rhs);
    lhs[2] = static_cast<T>(lhs[2] * rhs);
}

template <typename T, typename U>
void multiply(T (&lhs)[4], U rhs)
{
    lhs[0] = static_cast<T>(lhs[0] * rhs);
    lhs[1] = static_cast<T>(lhs[1] * rhs);
    lhs[2] = static_cast<T>(lhs[2] * rhs);
    lhs[3] = static_cast<T>(lhs[3] * rhs);
}

template <typename T>
void subtract(T (&lhs)[3], const T (&rhs)[3])
{
    lhs[0] -= rhs[0];
    lhs[1] -= rhs[1];
    lhs[2] -= rhs[2];
}

template <typename T>
void subtract(T (&lhs)[4], const T (&rhs)[4])
{
    lhs[0] -= rhs[0];
    lhs[1] -= rhs[1];
    lhs[2] -= rhs[2];
    lhs[3] -= rhs[3];
}

/** @}
  */
}}

#endif
