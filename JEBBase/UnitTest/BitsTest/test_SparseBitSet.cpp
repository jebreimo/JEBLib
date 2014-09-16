/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Bits/SparseBitSet.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Bits;

static void test_Construction()
{
    const size_t size = 100000;
    SparseBitSet set(size);
    JT_EQUAL(set.size(), size);
    size_t bitsSet = 0;
    for (size_t i = 0; i < size; i++)
        if (set.bit(i))
            bitsSet++;
    JT_EQUAL(bitsSet, 0);
    JT_EQUAL(set.usedBucketCount(), 0);
}

static void assign(SparseBitSet& set, size_t index)
{
    JT_EQUAL(set.bit(index), false);
    set.setBit(index, true);
    JT_EQUAL(set.bit(index), true);
    set.setBit(index, false);
    JT_EQUAL(set.bit(index), false);
}

static void test_Assignment()
{
    const size_t size = 100000;
    SparseBitSet set(size);

    JT_EQUAL(set.usedBucketCount(), 0);

    assign(set, 0);

    JT_EQUAL(set.usedBucketCount(), 1);

    assign(set, size - 1);

    JT_EQUAL(set.usedBucketCount(), 2);
}

JT_SUBTEST("Bits", test_Construction, test_Assignment);
