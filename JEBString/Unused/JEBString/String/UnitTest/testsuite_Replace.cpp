#include "../String.hpp"

#include <vector>
#include <JEBTest/JEBTest.hpp>

using namespace JEB;

static void test_replace()
{
    std::string test("abc_!_def_!_ghi");

    JT_EQUAL(String::replace(test, "_!_", "-#-"), "abc-#-def-#-ghi");
    JT_EQUAL(String::replace(test, "_!_", "-#-", 1), "abc-#-def_!_ghi");
    JT_EQUAL(String::replace(test, "_!_", "-#-", 0), "abc-#-def-#-ghi");
    JT_EQUAL(String::replace(test, "", "_#_"), test);
    JT_EQUAL(String::replace("", "Foo", ""), "");
    JT_EQUAL(String::replace("Foo", "Foo", ""), "");
    JT_EQUAL(String::replace("Foo", "", "Bar"), "Foo");
}

static void test_replaceCharacter()
{

    std::string s = "abc\xC2\xA0" "def\xC2\xA0ghi";
    JT_EQUAL(String::replace(s, 0xA0, ' '),
             std::string("abc def ghi"));
}

JT_TEST(test_replace, test_replaceCharacter);
