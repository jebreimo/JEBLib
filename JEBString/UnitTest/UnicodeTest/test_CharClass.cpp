#include "JEBString/Unicode/CharClass.hpp"
#include "JEBString/Unicode/UnicodeChars.hpp"
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace JEBString::Unicode;

void test_charClass()
{
    JT_EQUAL(charClass('\0'), CharClass::Control);
    JT_EQUAL(charClass(' '), CharClass::SpaceSeparator);
    JT_EQUAL(charClass('('), CharClass::OpenPunctuation);
    JT_EQUAL(charClass(')'), CharClass::ClosePunctuation);
    JT_EQUAL(charClass('-'), CharClass::DashPunctuation);
    JT_EQUAL(charClass('0'), CharClass::DecimalNumber);
    JT_EQUAL(charClass('A'), CharClass::UppercaseLetter);
    JT_EQUAL(charClass('q'), CharClass::LowercaseLetter);
    JT_EQUAL(charClass(LatinCapitalAe), CharClass::UppercaseLetter);
    JT_EQUAL(charClass(MultiplicationSign), CharClass::MathSymbol);
}

JT_SUBTEST("Unicode", test_charClass);

}
