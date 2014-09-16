/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Bits/Endian.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Bits;

void test_reverseBytes()
{
    uint8_t v8 = 0x81;
    JT_EQUAL(reverseBytes(v8), 0x81);
    uint16_t v16 = 0x8001;
    JT_EQUAL(reverseBytes(v16), 0x0180);
    uint32_t v32 = 0xC0800103u;
    JT_EQUAL(reverseBytes(v32), 0x030180C0);
    uint64_t v64 = 0xF0E0C0800103070F;
    JT_EQUAL(reverseBytes(v64), 0x0F07030180C0E0F0);
}

void test_swapEndianness()
{
    uint32_t value = 0x01020304u;
    swapEndianness<false>(value);
    JT_EQUAL(value, 0x01020304u);
    swapEndianness<true>(value);
    JT_EQUAL(value, 0x04030201u);
}

JT_SUBTEST("Bits",
           test_reverseBytes,
           test_swapEndianness);
