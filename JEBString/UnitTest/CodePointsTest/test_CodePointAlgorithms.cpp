#include "JEBString/CodePoints/CodePointAlgorithms.hpp"

#include <iterator>
#include "JEBString/CodePoints/CodePointIterator.hpp"
#include "JEBString/EncodedStrings/Utf8Encoding.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using JEBString::EncodedStrings::Utf8Encoding;
using JEBString::EncodedStrings::EncodedRange;
using namespace JEBString::CodePoints;

template <typename String, typename It, typename Enc>
String toString(EncodedRange<It, Enc> r)
{
    return String(begin(r), end(r));
}

void test_advanceWhileEqual()
{
    const char a[] = "a b c d e f g";
    const char b[] = "a b c d";
    auto aIt = makeForwardIterator(makeEncodedRange(a, Utf8Encoding()));
    auto bIt = makeForwardIterator(makeEncodedRange(b, Utf8Encoding()));
    JT_ASSERT(advanceWhileEqual(aIt, bIt));
    JT_EQUAL(std::string(begin(aIt), end(aIt)), " e f g");
}

void test_search()
{
    const char a[] = "a b c d e f g";
    std::string b("c d e");
    auto aIt = makeForwardIterator(makeEncodedRange(a, Utf8Encoding()));
    auto bIt = makeForwardIterator(makeEncodedRange(b, Utf8Encoding()));
    JT_EQUAL(toString<std::string>(makeEncodedRange(search(aIt, bIt))), "c d e");

    auto aRevIt = makeReverseIterator(makeEncodedRange(a, Utf8Encoding()));
    auto bRevIt = makeReverseIterator(makeEncodedRange(b, Utf8Encoding()));
    JT_EQUAL(toString<std::string>(makeEncodedRange(search(aRevIt, bRevIt))),
             "c d e");
}

JT_SUBTEST("CodePoints",
           test_advanceWhileEqual,
           test_search);

}
