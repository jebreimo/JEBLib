#include "../Generic/CharRangeSet.hpp"

#include <JEBTest/JEBTest.hpp>
#include "../Utf8/BiIterator.hpp"

using namespace JEB::String;
using namespace JEB::String::Generic;

static void test_Add()
{
    CharRangeSet set;
    JT_ASSERT(!set.has('b'));
    set.add('b');
    JT_ASSERT(!set.has('a'));
    JT_ASSERT(set.has('b'));
    JT_ASSERT(!set.has('c'));
    set.add('d');
    JT_ASSERT(set.has('b'));
    JT_ASSERT(!set.has('c'));
    JT_ASSERT(set.has('d'));
    JT_EQUAL(set.numberOfCharacters(), 2);
}

static void test_AddGaps()
{
    CharRangeSet set;
    set.add('a');
    set.add('c');
    set.add('e');
    set.add(CharRangeSet::Range('a', 'g'));
}

static void test_Efficiency()
{
    CharRangeSet set;
    set.add('A');
    JT_EQUAL(set.size(), 1);
    set.add('C');
    JT_EQUAL(set.size(), 2);
    set.add('B');
    JT_EQUAL(set.size(), 1);
    JT_EQUAL(set.numberOfCharacters(), 3);
    set.add('E');
    set.add('G');
    set.add('I');
    JT_EQUAL(set.size(), 4);
    JT_EQUAL(set.numberOfCharacters(), 6);
    set.add(CharRangeSet::Range('A', 'K'));
    JT_EQUAL(set.size(), 1);
    JT_EQUAL(set.numberOfCharacters(), 11);
}

CharRangeSet parse(const std::string& s)
{
    return CharRangeSet::parse(Utf8::begin(s), Utf8::end(s));
}
static void test_Parse()
{
    CharRangeSet set = parse("-\\n+F-Q2-8ab\\u0800");
    JT_ASSERT(set.has('-'));
    JT_ASSERT(set.has('\n'));
    JT_ASSERT(set.has('+'));
    JT_ASSERT(!set.has('.'));
    JT_ASSERT(set.hasAll(CharRangeSet::Range('F', 'Q')));
    JT_ASSERT(!set.has('E'));
    JT_ASSERT(!set.has('R'));
    JT_ASSERT(set.has('b'));
    JT_ASSERT(!set.has('c'));
    JT_ASSERT(set.has(0x800u));
    JT_ASSERT(!set.has(0x801u));
    JT_EQUAL(set.numberOfCharacters(), 25);
}

static void test_Complement()
{
    CharRangeSet set = parse("B-Yb-y");
    JT_ASSERT(set.has('b'));
    CharRangeSet complement = set.complement();
    JT_ASSERT(complement.has('A'));
    JT_ASSERT(!complement.has('B'));
    JT_ASSERT(!complement.has('Y'));
    JT_ASSERT(complement.has('Z'));
    JT_ASSERT(complement.has('a'));
    JT_ASSERT(!complement.has('b'));
    JT_ASSERT(!complement.has('y'));
    JT_ASSERT(complement.has('z'));

    // Test hasAll and hasAny while we're at it
    JT_ASSERT(complement.hasAll(CharRangeSet::Range('\0', 'A')));
    JT_ASSERT(!complement.hasAll(CharRangeSet::Range('\0', 'B')));
    JT_ASSERT(complement.hasAll(CharRangeSet::Range('Z', 'a')));
    JT_ASSERT(!complement.hasAll(CharRangeSet::Range('Z', 'b')));

    JT_ASSERT(!complement.hasAny(CharRangeSet::Range('B', 'Y')));
    JT_ASSERT(complement.hasAny(CharRangeSet::Range('A', 'Z')));
    JT_ASSERT(complement.hasAny(CharRangeSet::Range('B', 'Z')));
    JT_ASSERT(complement.hasAny(CharRangeSet::Range('Z', 'a')));
    JT_ASSERT(!complement.hasAny(CharRangeSet::Range('b', 'y')));
    JT_ASSERT(complement.hasAny(CharRangeSet::Range('a', 'b')));
    JT_ASSERT(complement.hasAny(CharRangeSet::Range('y', 'z')));
}

JT_TEST(test_Add,
        test_AddGaps,
        test_Efficiency,
        test_Parse,
        test_Complement);
