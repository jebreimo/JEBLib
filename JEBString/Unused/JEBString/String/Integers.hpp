#ifndef JEB_INTEGERS_HPP
#define JEB_INTEGERS_HPP

#include <algorithm>
#include <string>
#include "JEB/Bits/Bits.hpp"

namespace JEB
{
namespace Integers
{

template <typename T>
std::string binary(T bits, size_t len = sizeof(T) * 8)
{
    len = std::min(len - 1, sizeof(bits) * 8 - 1);
    std::string s(len + 1, '0');
    T mask = 1 << len;
    for (size_t i = 0; bits && i <= len; i++)
    {
        if (bits & mask)
        {
            s[i] = '1';
            bits &= ~mask; // Deals with negative signed integers.
        }
        mask >>= 1;
    }
    return s;
}

template <typename T>
std::string hexadecimal(T value, size_t width = 0)
{
    size_t maxBit = Bits::highestOne(value);
    size_t n;
    if (maxBit != std::numeric_limits<T>::max())
        n = std::max((maxBit + 3) / 4, width);
    else
        n = width;
    std::string s;
    while (n-- > 0)
    {
        size_t shift = n * 4;
        char digit = (char)((value >> shift) & 0xF);
        s += digit + (digit < 10 ? '0' : 'A' - 10);
    }
    return s;
}

}
}

#endif
