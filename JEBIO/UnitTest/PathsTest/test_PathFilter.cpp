#include "JEBIO/Paths/PathFilter.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBIO;

static void test_PathFilter()
{
    PathFilter filter;
    filter.includePath("a/b");
    filter.excludePath("a/b/c");
    filter.setType(ExclusiveFilter);
    JT_ASSERT(filter.shouldDescend("a"));
    JT_ASSERT(!filter.descend("a"));
    JT_ASSERT(!filter.shouldDescend("a"));
    JT_ASSERT(filter.shouldDescend("b"));
    JT_ASSERT(filter.descend("b"));
    JT_ASSERT(filter.shouldDescend("a"));
    JT_ASSERT(filter.shouldDescend("b"));
    JT_ASSERT(!filter.shouldDescend("c"));
}

JT_SUBTEST("Paths", test_PathFilter);
