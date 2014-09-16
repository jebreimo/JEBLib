/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Iterators/Iterators.hpp"
#include <list>
#include <vector>
#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Iterators;

namespace {

void test_Bi()
{
    int values[] = {1, 2, 3, 4, 5};
    std::list<int> list(std::begin(values), std::end(values));
    std::list<int>::iterator it;
    JT_ASSERT(nth(list.begin(), list.end(), 5) == list.end());
    JT_ASSERT(nth(list.begin(), list.end(), -5) == list.begin());
}

void test_Rnd()
{
    int values[] = {1, 2, 3, 4, 5};
    std::vector<int> list(std::begin(values), std::end(values));
    std::vector<int>::iterator it;
    JT_ASSERT(nth(list.begin(), list.end(), 5) == list.end());
    JT_ASSERT(nth(list.begin(), list.end(), -5) == list.begin());
}

JT_SUBTEST("Iterators", test_Bi, test_Rnd);

}
