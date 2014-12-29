/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Algorithms/KeyFunctionAlgorithms.hpp"
#include <vector>

#include <JEBTest/JEBTest.hpp>

using namespace JEBBase;

template <typename T>
static T square(T value)
{
    return value * value;
}

static void test_bounds()
{
    std::vector<int> values;
    for (int i = 0; i < 10; i++)
        values.push_back(i);
    std::vector<int>::const_iterator it;

    it = Algorithms::lowerBound(values.cbegin(), values.cend(), 9,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 3);

    it = Algorithms::upperBound(values.cbegin(), values.cend(), 9,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 4);

    it = Algorithms::lowerBound(values.cbegin(), values.cend(), 0,
                                 square<int>);
    JT_ASSERT(it == values.cbegin());
    JT_EQUAL(*it, 0);

    it = Algorithms::upperBound(values.cbegin(), values.cend(), 0,
                                 square<int>);
    JT_ASSERT(it != values.cbegin());
    JT_EQUAL(*it, 1);

    it = Algorithms::lowerBound(values.cbegin(), values.cend(), 81,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 9);

    it = Algorithms::upperBound(values.cbegin(), values.cend(), 81,
                                 square<int>);
    JT_ASSERT(it == values.cend());
}

JT_SUBTEST("KeyFunctionAlgorithms",
           test_bounds
           );
