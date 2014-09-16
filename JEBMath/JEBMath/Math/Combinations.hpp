#ifndef JEB_MATH_COMBINATIONS_HPP
#define JEB_MATH_COMBINATIONS_HPP

#include "JEBBase/Bits/BitIterator.hpp"
#include "JEBBase/Bits/Bits.hpp"
#include "Binomial.hpp"

namespace JEBMath { namespace Combinations {

namespace detail
{

template <typename T>
T localIndex(T combinations, size_t ones, size_t bits);

}

template <typename T>
T index(T combinations, size_t bits = sizeof(T) * 8)
{
    assert(bits == sizeof(T) * 8 ||
           (~(((T)1 << bits) - (T)1) & combinations) == 0);

    if (combinations == 0)
        return 0;

    size_t ones = JEBBase::Bits::countOnes(combinations);
    T index = 0;
    for (size_t i = 0; i < ones; i++)
        index += binomial<T>((T)bits, (T)i);
    return index + detail::localIndex(combinations, ones, bits);
}

template <typename T>
T localIndex(T combinations, size_t bits = sizeof(T) * 8)
{
    assert(bits == sizeof(T) * 8 ||
           (~(((T)1 << bits) - (T)1) & combinations) == 0);

    if (combinations == 0)
        return 0;

    size_t ones = JEBBase::Bits::countOnes(combinations);
    return detail::localIndex(combinations, ones, bits);
}

namespace detail
{

template <typename T>
T localIndex(T combinations, size_t ones, size_t bits)
{
    T index = 0;
    JEBBase::Bits::BitIterator<T> it(combinations);
    size_t aPrev = 0;
    size_t D = 0;
    for (size_t i = 1; i < ones; i++)
    {
        size_t a = it.next() + 1;
        size_t d = a - aPrev;
        for (size_t j = 1; j < d; j++)
            index += binomial<T>(static_cast<T>(bits - D - j),
                                 static_cast<T>(ones - i));
        D += d;
        aPrev = a;
    }
    return static_cast<T>(index + it.next() - aPrev);
}

}

}}

#endif
