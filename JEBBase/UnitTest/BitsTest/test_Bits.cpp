/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Bits/Bits.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Bits;

static void test_LowestOneInRange()
{
    unsigned bits = 0;
    size_t n = sizeof(bits) * 8;
    JT_EQUAL(lowestOneInRange(bits, 0, 10), SIZE_MAX);
    JT_EQUAL(lowestOneInRange(bits, 0, n), SIZE_MAX);
    bits = 0x800;
    JT_EQUAL(lowestOneInRange(bits, 0, n), 11);
    JT_EQUAL(lowestOneInRange(bits, 10, n), 11);
    JT_EQUAL(lowestOneInRange(bits, 11, n), 11);
    JT_EQUAL(lowestOneInRange(bits, 11, 12), 11);
    JT_EQUAL(lowestOneInRange(bits, 11, 22), 11);
    JT_EQUAL(lowestOneInRange(bits, 11, 1000), 11);
    bits = ~(unsigned)0;
    JT_EQUAL(lowestOneInRange(bits, n, 1000), SIZE_MAX);
}

JT_SUBTEST("Bits", test_LowestOneInRange);
