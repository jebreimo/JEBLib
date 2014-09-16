#include "JEBString/Unicode/CharMap.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBString::Unicode;

CompactCharMapping CompactLowerCaseMappings[] =
{
    {0x000040, 0x00000020, 0x07FFFFFE, 0xF8000001},
    {0x0000C0, 0x00000020, 0x7F7FFFFF, 0x80800000},
    {0x000160, 0x00000001, 0x2A555555, 0xD4AAAAAA},
    {0x000200, 0x00000001, 0x55555555, 0xAAAAAAAA}
};

CharMapping LowerCaseMappings[] =
{
    {0x000178, 0x0000FF},
    {0x000220, 0x00019E}
};

static void test_Get()
{
    CharMap map(CompactLowerCaseMappings, LowerCaseMappings);
    JT_EQUAL(map.get('G'), 'g');
    JT_EQUAL(map.get('g'), 'g');
    JT_EQUAL(map.get('-'), '-');
    JT_EQUAL(map.get(0xC0), 0xE0);
    JT_EQUAL(map.get(0xE3), 0xE3);
    JT_EQUAL(map.get(0xFF), 0xFF);
    JT_EQUAL(map.get(0x178), 0xFF);
    JT_EQUAL(map.get(0x200), 0x201);
    JT_EQUAL(map.get(0x220), 0x19E);
}

JT_SUBTEST("Unicode", test_Get);
