#include "../Utf8/EscapedFwdIt.hpp"

#include "../Utf8/Utf8Chars.hpp"
#include "JEB/Unicode/UnicodeChars.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEB::String::Utf8;

static void test_readEscapedString()
{
    std::string str = "Ab\\n\\\\c\\x33\\u10FF\\-" JEB_UTF8_THIN_SPACE "\\" JEB_UTF8_THIN_SPACE;
    typedef EscapedFwdIt<std::string::const_iterator> It;
    It it(str.begin(), str.end());
    It end(str.end(), str.end());
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, 'A');
    JT_ASSERT(!it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, 'b');
    JT_ASSERT(!it->second);
    JT_EQUAL((it++)->first, 'b');
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, '\n');
    JT_ASSERT(it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, '\\');
    JT_ASSERT(it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, 'c');
    JT_ASSERT(!it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, 0x33);
    JT_ASSERT(it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, 0x10FF);
    JT_ASSERT(it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, '-');
    JT_ASSERT(it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, JEB::Unicode::ThinSpace);
    JT_ASSERT(!it->second);
    ++it;
    JT_ASSERT(it != end);
    JT_EQUAL(it->first, JEB::Unicode::ThinSpace);
    JT_ASSERT(it->second);
}

JT_TEST(test_readEscapedString);
