#include "../Utf8/Finder.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEB;
using namespace JEB::String;

typedef std::pair<std::string::const_iterator, std::string::const_iterator> StringRange;

static void test_firstFinder()
{
    std::string s = "Kjell er stor. Kjell er liten.";
    StringRange range = Utf8::firstFinder("Kjell")(s.begin(), s.end());
    JT_ASSERT(range.first != range.second);
    JT_EQUAL(std::string(range.first, range.second), "Kjell");
    JT_EQUAL(std::distance(s.cbegin(), range.first), 0);
}

static void test_lastFinder()
{
    //std::string s
}

static void test_tokenFinder()
{
    std::string s = "TjelL er stokk.";
    //StringRange range = Utf8::tokenFinder("Ll")(s.begin(), s.end());
    // JT_ASSERT(range.first != range.second);
    // JT_EQUAL(std::string(range.first, range.second), "l");
    // JT_EQUAL(std::distance(s.cbegin(), range.first), 3);
    // range = Utf8::adaptFinder(tokenFinder("a-z", true))(s.begin(), s.end());
    // JT_ASSERT(range.first != range.second);
    // JT_EQUAL(std::string(range.first, range.second), "jel");
    // JT_EQUAL(std::distance(s.cbegin(), range.first), 1);
}

JT_TEST(test_firstFinder, test_lastFinder, test_tokenFinder);
