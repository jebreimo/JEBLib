#include "JEBString/Encodings/StringConverter.hpp"
#include "JEBString/Utf8/Utf8Chars.hpp"

#include <JEBTest/JEBTest.hpp>

using JEBString::Encoding;
using namespace JEBString::Encodings;

static void test_Utf8ToUtf16()
{
    char srcBuffer[] = "AB" UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "C";
    char utf16Buffer[8];
    std::pair<size_t, size_t> result;

    char utf16LEExpected[] = "A\0B\0\xC5\0C\0";
    result = convert(srcBuffer, sizeof(srcBuffer), Encoding::Utf8,
                     utf16Buffer, sizeof(utf16Buffer), Encoding::Utf16);
    JT_EQUAL(result.first, 5);
    JT_EQUAL(result.second, 8);
    JT_ASSERT(memcmp(utf16Buffer, utf16LEExpected, sizeof(utf16Buffer)) == 0);

    char utf16BEExpected[] = "\0A\0B\0\xC5\0C";
    result = convert(srcBuffer, sizeof(srcBuffer), Encoding::Utf8,
                     utf16Buffer, sizeof(utf16Buffer), Encoding::Utf16BE);
    JT_EQUAL(result.first, 5);
    JT_EQUAL(result.second, 8);
    JT_ASSERT(memcmp(utf16Buffer, utf16BEExpected, sizeof(utf16Buffer)) == 0);
}

static void test_Utf16LEToUtf16BE()
{
    char srcBuffer[] = "A\0B\0\xC5\0C\0";
    std::pair<size_t, size_t> result;

    char beBuffer[8];
    char beExpected[] = "\0A\0B\0\xC5\0C";
    result = convert(srcBuffer, sizeof(srcBuffer), Encoding::Utf16,
                     beBuffer, sizeof(beBuffer), Encoding::Utf16BE);
    JT_EQUAL(result.first, 8);
    JT_EQUAL(result.second, 8);
    JT_ASSERT(memcmp(beBuffer, beExpected, sizeof(beBuffer)) == 0);

    char leBuffer[8];
    char leExpected[] = "A\0B\0\xC5\0C\0";
    result = convert(beBuffer, sizeof(beBuffer), Encoding::Utf16BE,
                     leBuffer, sizeof(leBuffer), Encoding::Utf16LE);
    JT_EQUAL(result.first, 8);
    JT_EQUAL(result.second, 8);
    JT_ASSERT(memcmp(leBuffer, leExpected, sizeof(leBuffer)) == 0);
}

JT_SUBTEST("Encodings",
           test_Utf8ToUtf16,
           test_Utf16LEToUtf16BE);
