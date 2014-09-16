/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_UNION16_HPP
#define JEBBASE_BITS_UNION16_HPP

#include <algorithm>
#include <cstdint>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Bits {

union Union16
{
    Union16() : u16(0) {}
    explicit Union16(uint16_t n) : u16(n) {}

    template <typename T>
    explicit Union16(const T (&n)[2]);

    void reverse();

    uint16_t u16;
    int16_t i16;
    uint8_t u8[2];
    int8_t i8[2];
};

template <typename T>
Union16::Union16(const T (&n)[2])
{
    u8[0] = static_cast<uint8_t>(n[0]);
    u8[1] = static_cast<uint8_t>(n[1]);
}

inline void Union16::reverse()
{
    std::swap(u8[0], u8[1]);
}

}}

#endif
