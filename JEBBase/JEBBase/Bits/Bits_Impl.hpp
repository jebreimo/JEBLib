/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_BITS_BITS_IMPL_HPP
#define JEB_BITS_BITS_IMPL_HPP

#include <cassert>
#include <limits>

/** @file
  * @brief Implements the functions declared in Bits.hpp
  */

namespace JEBBase { namespace Bits {

namespace
{
    template <typename T>
    T makeMask(size_t n)
    {
        return n < sizeof(T) * 8 ? ((T)1 << n) - 1 : ~(T)0;
    }

    constexpr unsigned char oneCounts[] = {
            /* 0 */ 0, 1, 1, 2, /* 4 */ 1, 2, 2, 3,
            /* 8 */ 1, 2, 2, 3, /* C */ 2, 3, 3, 4};
}

template <typename T>
bool getBit(T bits, size_t index)
{
    assert(index < sizeof(T) * 8);
    return (bits & ((T)1 << index)) != 0;
}

template <typename T>
bool getBit(const T* bits, size_t bitsLen, size_t index)
{
    assert(index < sizeof(T) * bitsLen * 8);
    size_t major = index / (sizeof(T) * 8);
    size_t minor = index % (sizeof(T) * 8);
    return getBit(bits[major], minor);
}

template <typename T>
void setBit(T& bits, size_t index, bool value)
{
    assert(index < sizeof(T) * 8);
    if (value)
        bits |= ((T)1 << index);
    else
        bits &= ~((T)1 << index);
}

template <typename T>
bool setBit(T* bits, size_t bitsLen, size_t index, bool value)
{
    assert(index < sizeof(T) * bitsLen * 8);
    size_t major = index / (8 * sizeof(T));
    size_t minor = index % (8 * sizeof(T));
    return setBit(bits[major], minor, value);
}

template <typename T>
void invertBit(T& bits, size_t index)
{
    assert(index < sizeof(T) * 8);
    bits ^= ((T)1 << index);
}

template <typename T>
bool invertBit(T* bits, size_t bitsLen, size_t index, bool value)
{
    assert(index < sizeof(T) * bitsLen * 8);
    size_t major = index / (8 * sizeof(T));
    size_t minor = index % (8 * sizeof(T));
    return invertBit(bits[major], minor, value);
}

template <typename T>
size_t countOnes(T bits)
{
    size_t count = 0;
    do
    {
        count += oneCounts[bits & 0xF]
               + oneCounts[(bits >> 4) & 0xF]
               + oneCounts[(bits >> 8) & 0xF]
               + oneCounts[(bits >> 12) & 0xF];
       bits >>= 16;
    } while (bits != 0);
    return count;
}

template <typename T>
size_t countOnes(const T* bits, size_t bitsLen)
{
    size_t count = 0;
    for (size_t i = 0; i < bitsLen; i++)
        count += countOnes(bits[i]);
    return count;
}

template <typename T>
size_t lowestOne(T bits)
{
    if (bits == 0)
        return std::numeric_limits<size_t>::max();

    size_t index = 0;
    size_t shift = sizeof(bits) * 8;
    while (shift != 0)
    {
        shift /= 2;
        T lowerBits = bits << shift;
        if (lowerBits != 0)
            bits = lowerBits;
        else
            index += shift;
    }
    return index;
}

template <typename T>
size_t lowestOne(const T* bits, size_t bitsLen)
{
    for (size_t i = 0; i < bitsLen; i++)
    {
        if (bits[i])
            return i * sizeof(T) * 8 + lowestOne(bits[i]);
    }
    return std::numeric_limits<size_t>::max();
}

template <typename T>
size_t lowestOneInRange(T bits, size_t minIndex, size_t maxIndex)
{
    assert(minIndex <= maxIndex);
    if (minIndex >= sizeof(T) * 8)
        return std::numeric_limits<size_t>::max();

    T mask = makeMask<T>(maxIndex - minIndex);
    size_t index = lowestOne((bits >> minIndex) & mask);
    if (index != std::numeric_limits<size_t>::max())
        return minIndex + index;
    else
        return std::numeric_limits<size_t>::max();
}

template <typename T>
size_t highestOne(T bits)
{
    if (bits == 0)
        return std::numeric_limits<size_t>::max();

    size_t index = 0;
    size_t shift = sizeof(bits) * 8;
    while (shift != 0)
    {
        shift /= 2;
        T upperBits = bits >> shift;
        if (upperBits != 0)
        {
            bits = upperBits;
            index += shift;
        }
    }
    return index;
}

template <typename T>
size_t highestOne(const T* bits, size_t bitsLen)
{
    for (size_t i = bitsLen; i-- > 0;)
    {
        if (bits[i])
            return i * sizeof(T) * 8 + highestOne(bits[i]);
    }
    return std::numeric_limits<size_t>::max();
}

template <typename T>
size_t countOnesInRange(T bits, size_t minIndex, size_t maxIndex)
{
    assert(minIndex <= maxIndex);
    T mask = makeMask<T>(maxIndex - minIndex);
    return countOnes((bits >> minIndex) & mask);
}

template <typename T>
size_t nthOne(T bits, size_t n)
{
    assert(n < sizeof(T) * 8);

    size_t index = 0;
    while (bits != 0 && oneCounts[bits & 0xF] < n)
    {
        n -= oneCounts[bits & 0xF];
        bits >>= 4;
        index += 4;
    }

    while (bits != 0)
    {
        if ((bits & 1) == 1)
        {
            --n;
            if (n == 0)
                return index;
        }
        bits >>= 1;
        ++index;
    }

    return std::numeric_limits<size_t>::max();
}

template <typename T>
bool isPowerOfTwo(T bits)
{
    return bits && (bits & (bits - 1)) == 0;
}

}}

#endif
