/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Algorithms/Algorithms.hpp"
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

    it = Algorithms::lower_bound(values.cbegin(), values.cend(), 9,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 3);

    it = Algorithms::upper_bound(values.cbegin(), values.cend(), 9,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 4);

    it = Algorithms::lower_bound(values.cbegin(), values.cend(), 0,
                                 square<int>);
    JT_ASSERT(it == values.cbegin());
    JT_EQUAL(*it, 0);

    it = Algorithms::upper_bound(values.cbegin(), values.cend(), 0,
                                 square<int>);
    JT_ASSERT(it != values.cbegin());
    JT_EQUAL(*it, 1);

    it = Algorithms::lower_bound(values.cbegin(), values.cend(), 81,
                                 square<int>);
    JT_ASSERT(it != values.cend());
    JT_EQUAL(*it, 9);

    it = Algorithms::upper_bound(values.cbegin(), values.cend(), 81,
                                 square<int>);
    JT_ASSERT(it == values.cend());
}

static void test_search_last()
{
    int values[] = {1, 2, 3, 4, 1, 2, 3, 5, 1, 2, 3, 6};
    int search[] = {2, 3};

    std::pair<int*, int*> match = Algorithms::search_last(
            std::begin(values), std::end(values),
            std::begin(search), std::end(search));
    JT_ASSERT(match.first != match.second);
    JT_EQUAL(std::distance(match.first, match.second), 2);
    JT_EQUAL(std::distance(match.first, std::end(values)), 3);
    JT_EQUAL(*match.first, 2);
}

static void test_search_last_partialMatch()
{
    int values[] = {2, 3, 6, 7, 4, 1, 2, 3, 6, 5, 1, 2, 3, 6};
    int search[] = {2, 3, 6, 7};

    std::pair<int*, int*> match = Algorithms::search_last(
            std::begin(values), std::end(values),
            std::begin(search), std::end(search));
    JT_ASSERT(match.first != match.second);
    JT_EQUAL(std::distance(match.first, match.second), 4);
    JT_EQUAL(std::distance(std::begin(values), match.first), 0);
    JT_EQUAL(*match.first, 2);
}

JT_SUBTEST("Algorithms",
           test_bounds,
           test_search_last,
           test_search_last_partialMatch
           );
