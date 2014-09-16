/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_UNION32_HPP
#define JEBBASE_BITS_UNION32_HPP

#include <algorithm>
#include <cstdint>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Bits {

union Union32
{
    Union32() : u32(0) {}
    explicit Union32(uint32_t n) : u32(n) {}

    template <typename T>
    explicit Union32(const T (&n)[2]);

    template <typename T>
    explicit Union32(const T (&n)[4]);

    void reverse();

    int32_t i32;
    uint32_t u32;
    int16_t i16[2];
    uint16_t u16[2];
    int8_t i8[4];
    uint8_t u8[4];
};

template <typename T>
Union32::Union32(const T (&n)[2])
{
    u16[0] = static_cast<uint16_t>(n[0]);
    u16[1] = static_cast<uint16_t>(n[1]);
}

template <typename T>
Union32::Union32(const T (&n)[4])
{
    u8[0] = static_cast<uint8_t>(n[0]);
    u8[1] = static_cast<uint8_t>(n[1]);
    u8[2] = static_cast<uint8_t>(n[2]);
    u8[3] = static_cast<uint8_t>(n[3]);
}

inline void Union32::reverse()
{
    std::swap(u8[0], u8[3]);
    std::swap(u8[1], u8[2]);
}

}}

#endif
