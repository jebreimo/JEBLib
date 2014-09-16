/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/Containers/IntervalMap.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::Containers;

void test_Find()
{
    typedef IntervalMap<double, int> Map;
    Map map;
    map.insert(0.1, 1.0, 0);
    map.insert(0.1, 0.3, 1);
    map.insert(0.6, 0.8, 5);
    map.insert(0.8, 1.0, 6);
    map.insert(0.25, 0.5, 2);
    map.insert(0.45, 0.65, 3);
    map.insert(0.5, 0.6, 4);
    map.insert(1.0, 1.0001, 7);
    map.insert(1.5, 2.0, 8);

    Map::const_iterator it;
    it = map.find(0.0);
    JT_ASSERT(it == map.end());
    it = map.find(0.1);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 1);
    it = map.find(0.25);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 2);
    it = map.find(0.3);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 2);
    it = map.find(0.45);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 3);
    it = map.find(0.5);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 4);
    it = map.find(0.6);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 3);
    it = map.find(0.65);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 5);
    it = map.find(0.8);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 6);
    it = map.find(1.0);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 7);
    it = map.find(1.1);
    JT_ASSERT(it == map.end());
    it = map.find(1.75);
    JT_ASSERT(it != map.end());
    JT_EQUAL(it->second, 8);
    it = map.find(2.0);
    JT_ASSERT(it == map.end());
}

JT_SUBTEST("Containers", test_Find);
