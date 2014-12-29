/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Ranges/RangeAlgorithms.hpp"
#include <array>
#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Ranges;

namespace {

void test_countIf()
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1};
    JT_EQUAL(countIf(makeRange(values), [](auto c){return c > 5;}), 3);
}

void test_transform()
{
    auto values = std::vector<int> {1, 2, 3, 4, 5, 6, 7};
    transform(makeRange(values), begin(values), [](auto v) {return v * v;});
    int expected[] = {1, 4, 9, 16, 25, 36, 49};
    JT_ASSERT(equal(makeRange(values), makeRange(expected)));
}

JT_SUBTEST("Ranges", test_countIf, test_transform);

}
