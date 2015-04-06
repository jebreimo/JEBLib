/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Bits/Bits.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBBase::Bits;

void test_LowestOneInRange()
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

void test_powerOfTwoFloor()
{
    JT_EQUAL(powerOfTwoFloor(0x0), 0x0);
    JT_EQUAL(powerOfTwoFloor(0x7FF), 0x400);
    JT_EQUAL(powerOfTwoFloor(0x800), 0x800);
    JT_EQUAL(powerOfTwoFloor(0x801), 0x800);
    JT_EQUAL(powerOfTwoFloor(0xFFF), 0x800);
}

void test_powerOfTwoCeiling()
{
    JT_EQUAL(powerOfTwoCeiling(0x0), 0x0);
    JT_EQUAL(powerOfTwoCeiling(0x7FF), 0x800);
    JT_EQUAL(powerOfTwoCeiling(0x800), 0x800);
    JT_EQUAL(powerOfTwoCeiling(0x801), 0x1000);
    JT_EQUAL(powerOfTwoCeiling(0xFFF), 0x1000);
}

JT_SUBTEST("Bits",
           test_LowestOneInRange,
           test_powerOfTwoCeiling,
           test_powerOfTwoFloor);

}
