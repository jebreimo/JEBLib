/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_UNION64_HPP
#define JEBBASE_BITS_UNION64_HPP

#include <algorithm>
#include <cstdint>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Bits {

union Union64
{
    Union64() : u64(0) {}
    explicit Union64(uint64_t n) : u64(n) {}

    template <typename T>
    explicit Union64(const T (&n)[2]);

    template <typename T>
    explicit Union64(const T (&n)[4]);

    template <typename T>
    explicit Union64(const T (&n)[8]);

    void reverse();

    int64_t i64;
    uint64_t u64;
    int32_t i32[2];
    uint32_t u32[2];
    int16_t i16[4];
    uint16_t u16[4];
    int8_t i8[8];
    uint8_t u8[8];
};

template <typename T>
Union64::Union64(const T (&n)[2])
{
    u32[0] = static_cast<uint32_t>(n[0]);
    u32[1] = static_cast<uint32_t>(n[1]);
}

template <typename T>
Union64::Union64(const T (&n)[4])
{
    u16[0] = static_cast<uint16_t>(n[0]);
    u16[1] = static_cast<uint16_t>(n[1]);
    u16[2] = static_cast<uint16_t>(n[2]);
    u16[3] = static_cast<uint16_t>(n[3]);
}

template <typename T>
Union64::Union64(const T (&n)[8])
{
    u8[0] = static_cast<uint8_t>(n[0]);
    u8[1] = static_cast<uint8_t>(n[1]);
    u8[2] = static_cast<uint8_t>(n[2]);
    u8[3] = static_cast<uint8_t>(n[3]);
    u8[4] = static_cast<uint8_t>(n[4]);
    u8[5] = static_cast<uint8_t>(n[5]);
    u8[6] = static_cast<uint8_t>(n[6]);
    u8[7] = static_cast<uint8_t>(n[7]);
}

inline void Union64::reverse()
{
    std::swap(u8[0], u8[7]);
    std::swap(u8[1], u8[6]);
    std::swap(u8[2], u8[5]);
    std::swap(u8[3], u8[4]);
}

}}

#endif // UNION64_HPP
