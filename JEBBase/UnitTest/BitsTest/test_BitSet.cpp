/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Bits/BitSet.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Bits;

static void test_Assignment()
{
    BitSet bits(1000);
    JT_EQUAL(bits.size(), 1000);
    for (size_t i = 0; i < bits.size(); i++)
        JT_EQUAL(bits.bit(i), false);
    bits.setBit(0, true);
    JT_EQUAL(bits.bit(0), true);
    for (size_t i = 1; i < bits.size(); i++)
        JT_EQUAL(bits.bit(i), false);
    bits.setBit(999, true);
    JT_EQUAL(bits.bit(999), true);
    for (size_t i = 1; i < bits.size() - 1; i++)
        JT_EQUAL(bits.bit(i), false);
}

static void test_FindFirst()
{
    BitSet bits(512);
    JT_EQUAL(bits.findFirst(false), 0);
    JT_EQUAL(bits.findFirst(true), BitSet::NotFound);
    bits.setBit(511, true);
    JT_EQUAL(bits.findFirst(true), 511);
    bits.setBit(0, true);
    JT_EQUAL(bits.findFirst(false), 1);
    JT_EQUAL(bits.findFirst(true), 0);
    JT_EQUAL(bits.findFirst(true, 1), 511);
    JT_EQUAL(bits.findFirst(true, 511), 511);
    JT_EQUAL(bits.findFirst(false, 512), BitSet::NotFound);
    JT_EQUAL(bits.findFirst(true, 512), BitSet::NotFound);

    bits = BitSet(57);
    bits.setBit(32, true);
    bits.setBit(56, true);
    JT_EQUAL(bits.findFirst(true, 40), 56);
}

JT_SUBTEST("Bits", test_Assignment, test_FindFirst);
