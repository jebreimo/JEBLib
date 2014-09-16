#ifndef JEB_MATH_RATIONAL_HPP
#define JEB_MATH_RATIONAL_HPP

#include <cstdlib>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

namespace detail
{
    template <typename T>
    void reduceUnsignedFraction(T& a, T& b);
}

template <typename T>
T gcd(T a, T b)
{
    while (b != 0)
    {
        T tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

template <typename T>
void reduceFraction(T& a, T& b)
{
    T cd = abs(gcd(a, b));
    if (cd > 1)
    {
        a /= cd;
        b /= cd;
    }
}

template <>
inline void reduceFraction<unsigned char>(unsigned char& a, unsigned char& b)
{
    detail::reduceUnsignedFraction(a, b);
}

template <>
inline void reduceFraction<unsigned short>(unsigned short& a, unsigned short& b)
{
    detail::reduceUnsignedFraction(a, b);
}

template <>
inline void reduceFraction<unsigned>(unsigned& a, unsigned& b)
{
    detail::reduceUnsignedFraction(a, b);
}

template <>
inline void reduceFraction<unsigned long>(unsigned long& a, unsigned long& b)
{
    detail::reduceUnsignedFraction(a, b);
}

template <>
inline void reduceFraction<unsigned long long>(unsigned long long& a, unsigned long long& b)
{
    detail::reduceUnsignedFraction(a, b);
}

namespace detail
{
    template <typename T>
    void reduceUnsignedFraction(T& a, T& b)
    {
        T cd = gcd(a, b);
        if (cd > 1)
        {
            a /= cd;
            b /= cd;
        }
    }
}

}

#endif
