#include "JEBString/Unicode/CaseConverter.hpp"
#include "JEBString/Unicode/UnicodeChars.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBString::Unicode;

static void test_upperCase()
{
    JT_EQUAL(upper('A'), 'A');
    JT_EQUAL(upper('a'), 'A');
    JT_EQUAL(upper('Z'), 'Z');
    JT_EQUAL(upper('z'), 'Z');
    JT_EQUAL(upper(':'), ':');
    JT_EQUAL(upper(','), ',');

    JT_EQUAL(upper(0x00E0), 0x00C0);
    JT_EQUAL(upper(0x00E5), 0x00C5);
    JT_EQUAL(upper(0x00F8), 0x00D8);

    JT_EQUAL(upper(0x00FF), 0x0178);

    JT_EQUAL(upper(0x0106), 0x0106);
    JT_EQUAL(upper(0x0107), 0x0106);

    JT_EQUAL(upper(0x0174), 0x0174);
    JT_EQUAL(upper(0x0175), 0x0174);

    JT_EQUAL(upper(0x01C4), 0x01C4);
    JT_EQUAL(upper(0x01C5), 0x01C4);
    JT_EQUAL(upper(0x01C6), 0x01C4);
}

static void test_lowerCase()
{
    JT_EQUAL(lower('A'), 'a');
    JT_EQUAL(lower('a'), 'a');
    JT_EQUAL(lower('Z'), 'z');
    JT_EQUAL(lower('z'), 'z');
    JT_EQUAL(lower(':'), ':');
    JT_EQUAL(lower(','), ',');

    JT_EQUAL(lower(0x00C0), 0x00E0);
    JT_EQUAL(lower(0x00C5), 0x00E5);
    JT_EQUAL(lower(0x00D8), 0x00F8);
    JT_EQUAL(lower(0x0178), 0x00FF);

    JT_EQUAL(lower(0x01C4), 0x01C6);
    JT_EQUAL(lower(0x01C5), 0x01C6);
    JT_EQUAL(lower(0x01C6), 0x01C6);
}

static void test_titleCase()
{
    JT_EQUAL(title('A'), 'A');
    JT_EQUAL(title('a'), 'A');
    JT_EQUAL(title('Z'), 'Z');
    JT_EQUAL(title('z'), 'Z');
    JT_EQUAL(title(':'), ':');
    JT_EQUAL(title(','), ',');

    JT_EQUAL(title(0x00E0), 0x00C0);
    JT_EQUAL(title(0x00E5), 0x00C5);
    JT_EQUAL(title(0x00F8), 0x00D8);

    JT_EQUAL(title(0x00FF), 0x0178);

    JT_EQUAL(title(0x0106), 0x0106);
    JT_EQUAL(title(0x0107), 0x0106);

    JT_EQUAL(title(0x0174), 0x0174);
    JT_EQUAL(title(0x0175), 0x0174);

    JT_EQUAL(title(0x01C4), 0x01C5);
    JT_EQUAL(title(0x01C5), 0x01C5);
    JT_EQUAL(title(0x01C6), 0x01C5);
}

// static void test_isCase()
// {
//     JT_ASSERT(isLower('*'));
//     JT_ASSERT(isTitle('*'));
//     JT_ASSERT(isUpper('*'));

//     JT_ASSERT(!isLower('A'));
//     JT_ASSERT(isTitle('A'));
//     JT_ASSERT(isUpper('A'));

//     JT_ASSERT(isLower('['));
//     JT_ASSERT(isTitle('['));
//     JT_ASSERT(isUpper('['));

//     JT_ASSERT(isLower('a'));
//     JT_ASSERT(!isTitle('a'));
//     JT_ASSERT(!isUpper('a'));

//     JT_ASSERT(!isLower(JEB_CHAR_LATIN_CAPITAL_AE));
//     JT_ASSERT(isTitle(JEB_CHAR_LATIN_CAPITAL_AE));
//     JT_ASSERT(isUpper(JEB_CHAR_LATIN_CAPITAL_AE));

//     JT_ASSERT(isLower(JEB_CHAR_LATIN_SMALL_AE));
//     JT_ASSERT(!isTitle(JEB_CHAR_LATIN_SMALL_AE));
//     JT_ASSERT(!isUpper(JEB_CHAR_LATIN_SMALL_AE));
// }

JT_SUBTEST("Unicode", test_upperCase, test_lowerCase, test_titleCase);
