#include "JEBString/Unicode/CharMappingTypes.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBString::Unicode;

static void test_Get()
{
    CompactCharMapping ccs = {0x40, 0x20, 0x07FFFDFE, 0xF8000001};
    uint32_t lcase;
    JT_ASSERT(ccs.get(0x40, lcase));
    JT_EQUAL(lcase, 0x40);
    JT_ASSERT(ccs.get('A', lcase));
    JT_EQUAL(lcase, 'a');
    JT_ASSERT(!ccs.get('I', lcase));
    JT_ASSERT(ccs.get('Z', lcase));
    JT_EQUAL(lcase, 'z');
    JT_ASSERT(ccs.get(0x5B, lcase));
    JT_EQUAL(lcase, 0x5B);
}

JT_SUBTEST("Unicode", test_Get);
