/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_ENDIAN_HPP
#define JEBBASE_BITS_ENDIAN_HPP

#include "Union16.hpp"
#include "Union32.hpp"
#include "Union64.hpp"

#define JB_LITTLE_ENDIAN

namespace JEBBase { namespace Bits {

#ifdef JB_LITTLE_ENDIAN

static const bool IsBigEndian = false;

#else

static const bool IsBigEndian = true;

#endif

static const bool IsLittleEndian = !IsBigEndian;

enum Endianness
{
    UnknownEndianness,
    BigEndian,
    LittleEndian
};

/** @brief Returns the system's endianness.
 */
inline Endianness systemEndianness()
{
    Union16 u(1);
    return u.u8[0] == 0 ? BigEndian : LittleEndian;
}

inline uint8_t reverseBytes(uint8_t v)
{
    return v;
}

inline int8_t reverseBytes(int8_t v)
{
    return v;
}

inline uint16_t reverseBytes(uint16_t v)
{
    Union16 u(v);
    u.reverse();
    return u.u16;
}

inline int16_t reverseBytes(int16_t v)
{
    return (int16_t)reverseBytes((uint16_t)v);
}

inline uint32_t reverseBytes(uint32_t v)
{
    Union32 u(v);
    u.reverse();
    return u.u32;
}

inline int32_t reverseBytes(int32_t v)
{
    return (int32_t)reverseBytes((uint32_t)v);
}

inline uint64_t reverseBytes(uint64_t v)
{
    Union64 u(v);
    u.reverse();
    return u.u64;
}

inline int64_t reverseBytes(int64_t v)
{
    return (int64_t)reverseBytes((uint64_t)v);
}

inline Union16 reverseBytes(Union16 value)
{
    value.reverse();
    return value;
}

inline Union32 reverseBytes(Union32 value)
{
    value.reverse();
    return value;
}

inline Union64 swap(Union64 value)
{
    value.reverse();
    return value;
}

template <bool SwapBytes, typename T>
struct EndianSwapper
{
};

template <typename T>
struct EndianSwapper<true, T>
{
    static void swap(T& value)
    {
        value = reverseBytes(value);
    }
};

template <typename T>
struct EndianSwapper<false, T>
{
    static void swap(T& value)
    {}
};

template <bool SwapBytes, typename T>
void swapEndianness(T& value)
{
    EndianSwapper<SwapBytes, T>::swap(value);
}

template <typename T>
T fromBigEndian(T value)
{
    EndianSwapper<IsLittleEndian, T>::swap(value);
    return value;
}

template <typename T>
T fromLittleEndian(T value)
{
    EndianSwapper<IsBigEndian, T>::swap(value);
    return value;
}

}}

#endif
