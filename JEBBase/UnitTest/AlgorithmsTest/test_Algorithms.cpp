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

static void test_searchLast()
{
    int values[] = {1, 2, 3, 4, 1, 2, 3, 5, 1, 2, 3, 6};
    int search[] = {2, 3};

    std::pair<int*, int*> match = Algorithms::searchLast(
            std::begin(values), std::end(values),
            std::begin(search), std::end(search));
    JT_ASSERT(match.first != match.second);
    JT_EQUAL(std::distance(match.first, match.second), 2);
    JT_EQUAL(std::distance(match.first, std::end(values)), 3);
    JT_EQUAL(*match.first, 2);
}

static void test_searchLast_partialMatch()
{
    int values[] = {2, 3, 6, 7, 4, 1, 2, 3, 6, 5, 1, 2, 3, 6};
    int search[] = {2, 3, 6, 7};

    std::pair<int*, int*> match = Algorithms::searchLast(
            std::begin(values), std::end(values),
            std::begin(search), std::end(search));
    JT_ASSERT(match.first != match.second);
    JT_EQUAL(std::distance(match.first, match.second), 4);
    JT_EQUAL(std::distance(std::begin(values), match.first), 0);
    JT_EQUAL(*match.first, 2);
}

JT_SUBTEST("Algorithms",
           test_searchLast,
           test_searchLast_partialMatch
           );
