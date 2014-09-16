#include "JEBString/Unicode/CaseInsensitive.hpp"
#include "JEBString/Unicode/UnicodeChars.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBString::Unicode;

static void test_equal()
{
    CaseInsensitiveEqual op;

    JT_ASSERT(op((uint32_t)100, (uint32_t)100));
    JT_ASSERT(op('a', 'a'));
    JT_ASSERT(!op('a', 'b'));
    JT_ASSERT(op('a', 'A'));
    JT_ASSERT(op('*', '*'));
}

JT_SUBTEST("Unicode", test_equal);
