#include "../String.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEB::String;

static void test_primitive()
{
    WildcardExpression expr = parseWildcards("abcdef");
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(!match(expr, "abdef"));
    JT_ASSERT(!match(expr, "abcdefg"));
    JT_ASSERT(!match(expr, "abcdeg"));
    JT_ASSERT(!match(expr, "zabcdef"));
}

static void test_star()
{
    WildcardExpression expr;
    expr = parseWildcards("*def");
    JT_ASSERT(match(expr, "def"));
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(!match(expr, "abcdefg"));
    expr = parseWildcards("abc*");
    JT_ASSERT(match(expr, "abc"));
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(!match(expr, "abdc"));
    JT_ASSERT(!match(expr, "fabc"));
    expr = parseWildcards("abc*def");
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(match(expr, "abc_q_def"));
    JT_ASSERT(!match(expr, "abcefg"));
    JT_ASSERT(!match(expr, "abcef"));
    expr = parseWildcards("*cde*");
    JT_ASSERT(match(expr, "cde"));
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(!match(expr, "abcefg"));
    expr = parseWildcards("ab*cd*ef");
    JT_ASSERT(match(expr, "abcdef"));
    JT_ASSERT(match(expr, "ab_cd_ef"));
    JT_ASSERT(!match(expr, "abc_def"));
}

static void test_set()
{
    WildcardExpression expr = parseWildcards("ab[0-8][A-Y]?*?q[a-f]");
    JT_ASSERT(match(expr, "ab0A__qa"));
    JT_ASSERT(match(expr, "ab8Y__qf"));
    JT_ASSERT(!match(expr, "ab9Z__qg"));
    JT_ASSERT(!match(expr, "ab0A_qa"));
    JT_ASSERT(match(expr, "ab0A,fsdfe+qa"));
}

static void test_find()
{
    WildcardExpression expr;
    std::pair<size_t, size_t> pos;
    std::string str = "_a_b_ab_ab_ba_ba_b_a";

    expr = parseWildcards("ab*ba");

    pos = indexes(str, findLongest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba_ba");
    pos = indexes(str, findShortest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba");

    expr = parseWildcards("ba*ab");

    pos = indexes(str, findLongest(expr, str));
    JT_EQUAL(pos.first, pos.second);
    pos = indexes(str, findShortest(expr, str));
    JT_EQUAL(pos.first, pos.second);

    expr = parseWildcards("*ab*ba");

    pos = indexes(str, findLongest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "_a_b_ab_ab_ba_ba");
    pos = indexes(str, findShortest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba");

    expr = parseWildcards("ab*ba*");

    pos = indexes(str, findLongest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba_ba_b_a");
    pos = indexes(str, findShortest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba");

    expr = parseWildcards("*ab*ba*");

    pos = indexes(str, findLongest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), str);
    pos = indexes(str, findShortest(expr, str));
    JT_NOT_EQUAL(pos.first, pos.second);
    JT_EQUAL(substring(str, pos), "ab_ab_ba");
}

void test_hasWildcards()
{
    JT_ASSERT(hasWildcards("a*b"));
    JT_ASSERT(hasWildcards("a\\*b"));
    JT_ASSERT(hasWildcards("a?b"));
    JT_ASSERT(hasWildcards("a\\?b"));
    JT_ASSERT(!hasWildcards("abc"));
    JT_ASSERT(!hasWildcards("a\\bc"));
    JT_ASSERT(hasWildcards("[a-z\\]]"));
    JT_ASSERT(!hasWildcards("[a-z]]"));
    JT_ASSERT(!hasWildcards("[a-z"));
    JT_ASSERT(!hasWildcards("\\[a-z\\]"));
}

JT_TEST(test_primitive, test_star, test_set, test_find, test_hasWildcards);
