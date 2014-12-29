#include "JEBString/Utf16/Utf16String.hpp"
#include "JEBString/Utf16/Utf16Chars.hpp"
#include "JEBString/Unicode/UnicodeChars.hpp"
#include "JEBString/Unicode/UnicodePredicates.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace JEBString;
using namespace JEBString::Utf16;

void test_append()
{
    std::wstring s;
    JT_EQUAL(append(s, Unicode::GreekSmallFinalSigma),
             UTF16_GREEK_SMALL_FINAL_SIGMA);
    JT_EQUAL(append(s, Unicode::PunctuationSpace),
             UTF16_GREEK_SMALL_FINAL_SIGMA UTF16_PUNCTUATION_SPACE);
}

void test_caseInsensitiveCompare()
{
    JT_LESS(caseInsensitiveCompare(L"aBc" UTF16_GREEK_SMALL_SIGMA,
                                    L"AbC" UTF16_GREEK_CAPITAL_SIGMA L"d"), 0);
    JT_LESS(caseInsensitiveCompare(L"aBc" UTF16_GREEK_SMALL_SIGMA L"d",
                                    L"AbC" UTF16_GREEK_CAPITAL_TAU), 0);
    JT_EQUAL(caseInsensitiveCompare(L"aBc" UTF16_GREEK_SMALL_SIGMA,
                                    L"AbC" UTF16_GREEK_CAPITAL_SIGMA), 0);
    JT_GREATER(caseInsensitiveCompare(L"aBc" UTF16_GREEK_SMALL_SIGMA L"a",
                                      L"AbC" UTF16_GREEK_CAPITAL_SIGMA), 0);
    JT_GREATER(caseInsensitiveCompare(L"aBc" UTF16_GREEK_SMALL_PSI L"d",
                                      L"AbC" UTF16_GREEK_CAPITAL_TAU), 0);
}

void test_caseInsensitiveEqual()
{
    JT_ASSERT(caseInsensitiveEqual(L"aBc" UTF16_GREEK_SMALL_SIGMA,
                                   L"AbC" UTF16_GREEK_CAPITAL_SIGMA));
}

void test_caseInsensitiveLess()
{
    JT_ASSERT(!caseInsensitiveLess(L"aBc" UTF16_GREEK_SMALL_SIGMA L"D",
                                   L"AbC" UTF16_GREEK_CAPITAL_SIGMA L"d"));
    JT_ASSERT(caseInsensitiveLess(L"aBc" UTF16_GREEK_SMALL_SIGMA L"d",
                                  L"AbC" UTF16_GREEK_CAPITAL_TAU));
}

void test_contains()
{
    JT_ASSERT(contains(L"ABCDE", 'D'));
    JT_ASSERT(!contains(L"ABCDE", 'F'));
}

void test_endsWith()
{
    JT_ASSERT(endsWith(L"aBc" UTF16_GREEK_SMALL_SIGMA L"D",
                       L"C" UTF16_GREEK_CAPITAL_SIGMA L"d",
                       FindFlags::CaseInsensitive));
    JT_ASSERT(!endsWith(L"aBc" UTF16_GREEK_SMALL_SIGMA L"D",
                        L"E" UTF16_GREEK_CAPITAL_SIGMA L"d",
                        FindFlags::CaseInsensitive));
}

void test_findSubstring()
{
    auto s = std::wstring(L"abc_ghIJ_gH" UTF16_GREEK_SMALL_SIGMA L"Ij_kLM_nop");
    auto r = findSubstring(s, L"gh" UTF16_GREEK_CAPITAL_SIGMA L"ij",
                           FindFlags::CaseInsensitive);
    JT_EQUAL(std::wstring(r.first, r.second),
             L"gH" UTF16_GREEK_SMALL_SIGMA L"Ij");
    auto t = findSubstring(r, UTF16_GREEK_CAPITAL_SIGMA L"i",
                           FindFlags::CaseInsensitive);
    JT_EQUAL(std::wstring(t.first, t.second), UTF16_GREEK_SMALL_SIGMA L"I");
    auto u = findSubstring(r, UTF16_GREEK_CAPITAL_SIGMA L"i");
    JT_ASSERT(u.first == u.second && u.second == r.second);
}

void test_insert()
{
    auto str = L"The " UTF16_GREEK_SMALL_OMEGA
               UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
               L" and the A" UTF16_COMBINING_INVERTED_BREVE
               UTF16_COMBINING_DOT_ABOVE ".";
    auto r = insert(insert(str, 13, L" insanely"), -2, L"great ");
    JT_EQUAL(r, L"The " UTF16_GREEK_SMALL_OMEGA
                 UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                 L" and the insanely great A" UTF16_COMBINING_INVERTED_BREVE
                 UTF16_COMBINING_DOT_ABOVE L".");
}

void test_insertChar()
{
    auto str = L"The " UTF16_GREEK_SMALL_OMEGA
               UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
               L" and the A" UTF16_COMBINING_INVERTED_BREVE
               UTF16_COMBINING_DOT_ABOVE L".";
    auto r = insert(str, 5, Unicode::GreekSmallFinalSigma);
    JT_EQUAL(r, L"The " UTF16_GREEK_SMALL_OMEGA
                UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                UTF16_GREEK_SMALL_FINAL_SIGMA
                L" and the A" UTF16_COMBINING_INVERTED_BREVE
                UTF16_COMBINING_DOT_ABOVE L".");
}

void test_insertInPlace()
{
    auto s = std::wstring(L"The " UTF16_GREEK_SMALL_OMEGA
                         UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                         L" and the A" UTF16_COMBINING_INVERTED_BREVE
                         UTF16_COMBINING_DOT_ABOVE L".");
    insertInPlace(insertInPlace(s, 13, L" insanely"), -2, L"great ");
    JT_EQUAL(s, L"The " UTF16_GREEK_SMALL_OMEGA
                 UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                 L" and the insanely great A" UTF16_COMBINING_INVERTED_BREVE
                 UTF16_COMBINING_DOT_ABOVE L".");
}

void test_isAlphaNumeric()
{
    JT_ASSERT(isAlphaNumeric(L"Ab1"));
    JT_ASSERT(!isAlphaNumeric(L"Ab-1"));
    JT_ASSERT(!isAlphaNumeric(L""));
    std::wstring s(L"2v" UTF16_GREEK_SMALL_OMEGA L"1A");
    JT_ASSERT(isAlphaNumeric(begin(s), end(s)));
}

void test_isValidUtf16()
{
    // JT_ASSERT(isValidUtf16("AB\xC1\x160"));
    // JT_ASSERT(!isValidUtf16("AB\xC0\xBF"));
}

void test_join()
{
    std::wstring strings[] = {L"foo", L"faa", L"fii", L"fee", L"fuu"};
    auto result1 = join(begin(strings), end(strings));
    JT_EQUAL(result1, L"foofaafiifeefuu");
    auto result2 = join(begin(strings), end(strings), L":-:");
    JT_EQUAL(result2, L"foo:-:faa:-:fii:-:fee:-:fuu");
}

void test_lower()
{
    JT_EQUAL(lower(L"aBc" UTF16_GREEK_CAPITAL_SIGMA L"d12$E"),
             L"abc" UTF16_GREEK_SMALL_SIGMA L"d12$e");
}

void test_nthCharacter()
{
    std::wstring str(L"The " UTF16_GREEK_SMALL_OMEGA
                    UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                    L" and the A" UTF16_COMBINING_INVERTED_BREVE
                    UTF16_COMBINING_DOT_ABOVE L".");
    JT_ASSERT(nthCharacter(str, 0) == begin(str));
    JT_ASSERT(nthCharacter(str, 4) == begin(str) + 4);
    JT_ASSERT(nthCharacter(str, 5) == begin(str) + 7);
    JT_ASSERT(nthCharacter(str, 14) == begin(str) + 16);
    JT_ASSERT(nthCharacter(str, 15) == begin(str) + 19);
    JT_ASSERT(nthCharacter(str, 16) == begin(str) + 20);
    JT_ASSERT(nthCharacter(str, 17) == begin(str) + 20);
    JT_ASSERT(nthCharacter(str, -1) == begin(str) + 19);
    JT_ASSERT(nthCharacter(str, -2) == begin(str) + 16);
    JT_ASSERT(nthCharacter(str, -16) == begin(str));
    JT_ASSERT(nthCharacter(str, -17) == begin(str));
}

void test_replace_indexes()
{
    auto s = L"The " UTF16_GREEK_SMALL_OMEGA
             UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
             L" and the A" UTF16_COMBINING_INVERTED_BREVE
             UTF16_COMBINING_DOT_ABOVE L".";
    JT_EQUAL(replace(s, 6, -3, L"beats no"),
             L"The " UTF16_GREEK_SMALL_OMEGA
             UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
             L" beats no A" UTF16_COMBINING_INVERTED_BREVE
             UTF16_COMBINING_DOT_ABOVE L".");
}

void test_replace_string()
{
    auto s = L"The " UTF16_GREEK_SMALL_OMEGA L" and the A.";
    JT_EQUAL(replace(s,
                     UTF16_GREEK_SMALL_OMEGA L" and",
                     UTF16_GREEK_CAPITAL_OMEGA L" or"),
             L"The " UTF16_GREEK_CAPITAL_OMEGA L" or the A.");
    JT_EQUAL(replace(s,
                     UTF16_GREEK_CAPITAL_OMEGA L" aNd",
                     UTF16_GREEK_CAPITAL_SIGMA L" or"),
             s);
    JT_EQUAL(replace(s,
                     UTF16_GREEK_CAPITAL_OMEGA L" aNd",
                     UTF16_GREEK_CAPITAL_SIGMA L" or",
                     0, FindFlags::CaseInsensitive),
             L"The " UTF16_GREEK_CAPITAL_SIGMA L" or the A.");
    JT_EQUAL(replace(s, UTF16_GREEK_SMALL_OMEGA L" and", L""), L"The  the A.");
    JT_EQUAL(replace(s, L"", L"foo"), s);
}

void test_replaceCodePoint()
{
    JT_EQUAL(replaceCodePoint(L"AB" UTF16_GREEK_SMALL_GAMMA L"D",
                              Unicode::GreekSmallGamma,
                              Unicode::FigureSpace),
             L"AB" UTF16_FIGURE_SPACE L"D");
    JT_EQUAL(replaceCodePoint(L"ABCDCDECDEFGCD", 'C', '_', 3),
             L"AB_D_DE_DEFGCD");
}

void test_replaceInPlace()
{
    auto s = std::wstring(L"The " UTF16_GREEK_SMALL_OMEGA
                          UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                          L" and the A" UTF16_COMBINING_INVERTED_BREVE
                          UTF16_COMBINING_DOT_ABOVE L".");
    replaceInPlace(s, 6, -3, L"beats no");
    JT_EQUAL(s, L"The " UTF16_GREEK_SMALL_OMEGA
                UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                L" beats no A" UTF16_COMBINING_INVERTED_BREVE
                UTF16_COMBINING_DOT_ABOVE L".");
}

void test_replaceInvalidUtf16()
{
    // auto s = "ABC\xC0\xBF" "DEF\xD0\x160\x160" "GH\xE16\x160" "I\xC16";
    // JT_EQUAL(replaceInvalidUtf16(s), "ABC??DEF\xD0\x160?GH??I?");
}

void test_replaceInvalidUtf16InPlace()
{
    // std::wstring s("ABC\xC0\xBF" "DEF\xD0\x160\x160" "GH\xE16\x160" "I\xC16");
    // JT_EQUAL(replaceInvalidUtf16InPlace(s), "ABC??DEF\xD0\x160?GH??I?");
}

void test_reverse()
{
    auto s = L"The " UTF16_GREEK_SMALL_OMEGA UTF16_COMBINING_BRIDGE_ABOVE
             UTF16_COMBINING_TILDE L" and the A" UTF16_COMBINING_INVERTED_BREVE
             UTF16_COMBINING_DOT_ABOVE L".";
    std::wstring result;
    reverse(s);
    JT_EQUAL(reverse(s),
             L".A" UTF16_COMBINING_INVERTED_BREVE UTF16_COMBINING_DOT_ABOVE
             L" eht dna " UTF16_GREEK_SMALL_OMEGA UTF16_COMBINING_BRIDGE_ABOVE
             UTF16_COMBINING_TILDE L" ehT");
}

void test_split_caseInsensitive()
{
    auto parts = split(L":" UTF16_GREEK_CAPITAL_OMEGA L"Q:foo:"
                       UTF16_GREEK_CAPITAL_OMEGA L"q:faa:"
                       UTF16_GREEK_SMALL_OMEGA L"Q:bor:"
                       UTF16_GREEK_SMALL_OMEGA L"q:",
                       L":" UTF16_GREEK_SMALL_OMEGA L"q:",
                       4,
                       SplitFlags::CaseInsensitive);
    JT_EQUAL(parts.size(), 4);
    JT_EQUAL(parts[0], L"");
    JT_EQUAL(parts[1], L"foo");
    JT_EQUAL(parts[2], L"faa");
    JT_EQUAL(parts[3], L"bor:" UTF16_GREEK_SMALL_OMEGA L"q:");
}

void test_split_whitespace()
{
    auto parts = split(L" foo faa\r\n\tfee bar " UTF16_EM_SPACE L"\tbor ");
    JT_EQUAL(parts.size(), 5);
    JT_EQUAL(parts[0], L"foo");
    JT_EQUAL(parts[1], L"faa");
    JT_EQUAL(parts[2], L"fee");
    JT_EQUAL(parts[3], L"bar");
    JT_EQUAL(parts[4], L"bor");
}

void test_splitIf()
{
    auto parts = splitIf(L" foo faa\r\n\tfee bar " UTF16_EM_SPACE L"\tbor ",
                         Unicode::isWhitespace, 0, SplitFlags::IgnoreEmpty);
    JT_EQUAL(parts.size(), 5);
    JT_EQUAL(parts[0], L"foo");
    JT_EQUAL(parts[1], L"faa");
    JT_EQUAL(parts[2], L"fee");
    JT_EQUAL(parts[3], L"bar");
    JT_EQUAL(parts[4], L"bor");
}

void test_splitLines()
{
    auto parts = splitLines(L" foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
    JT_EQUAL(parts.size(), 6);
    JT_EQUAL(parts[0], L" foo");
    JT_EQUAL(parts[1], L"faa ");
    JT_EQUAL(parts[2], L"\tfee bar ");
    JT_EQUAL(parts[3], L"bor");
    JT_EQUAL(parts[4], L"");
    JT_EQUAL(parts[5], L"rubb");
}

void test_startsWith()
{
    JT_ASSERT(startsWith(L"qF" UTF16_GREEK_SMALL_SIGMA L"aBcD",
                         L"qF" UTF16_GREEK_CAPITAL_SIGMA,
                         FindFlags::CaseInsensitive));
    JT_ASSERT(!startsWith(L"qF" UTF16_GREEK_SMALL_SIGMA L"aBcD",
                          L"qF" UTF16_GREEK_CAPITAL_SIGMA));
    JT_ASSERT(!startsWith(L"qF" UTF16_GREEK_SMALL_SIGMA L"aBcD",
                          L"qF" UTF16_GREEK_CAPITAL_SIGMA L"g",
                          FindFlags::CaseInsensitive));
}

void test_stringLength()
{
    JT_EQUAL(stringLength(L"A" UTF16_COMBINING_RING_ABOVE L"BCDE"
                          UTF16_COMBINING_TILDE),
             5);
}

void test_substring()
{
    std::wstring s(L"ABCD");
    JT_EQUAL(substring(s, 0), L"ABCD");
    JT_EQUAL(substring(s, 0, 5), L"ABCD");
    JT_EQUAL(substring(s, 1, 3), L"BC");
    JT_EQUAL(substring(s, 2, 2), L"");
    JT_EQUAL(substring(s, 3, 1), L"");
    JT_EQUAL(substring(s, 1, -1), L"BC");
    JT_EQUAL(substring(s, 2, -2), L"");
    JT_EQUAL(substring(s, 3, -4), L"");
    JT_EQUAL(substring(s, -3), L"BCD");
    JT_EQUAL(substring(s, -3, -1), L"BC");
    JT_EQUAL(substring(s, -2, -2), L"");
    JT_EQUAL(substring(s, -1, -3), L"");
}

void test_title()
{
    JT_EQUAL(title(L"aBc " UTF16_GREEK_SMALL_SIGMA L"De.fooB"),
             L"Abc " UTF16_GREEK_CAPITAL_SIGMA L"de.Foob");
}

void test_toUtf16()
{
    JT_EQUAL(toUtf16(L"Årbøker"), L"Årbøker");
    JT_EQUAL(toUtf16(L"Årbøker", Encoding::Utf16), L"Årbøker");
}

void test_trim()
{
    JT_EQUAL(trim(L" \n\t foo bar \f\r" UTF16_PARAGRAPH_SEPARATOR), L"foo bar");
    JT_EQUAL(trim(L":--." UTF16_GREEK_SMALL_SIGMA L"foo bar:--",
                  Unicode::isPunctuation),
             UTF16_GREEK_SMALL_SIGMA L"foo bar");
    JT_EQUAL(trim(L"A.BC_DFB.-GA-B", [](uint32_t c){return contains(L"AB.-", c);}),
             L"C_DFB.-G");
}

void test_trimFront()
{
    JT_EQUAL(trimFront(L" \n\t" UTF16_PARAGRAPH_SEPARATOR L" foo bar \f\r"),
             L"foo bar \f\r");
    JT_EQUAL(trimFront(L":--." UTF16_GREEK_SMALL_SIGMA L"foo bar:--",
                       Unicode::isPunctuation),
             UTF16_GREEK_SMALL_SIGMA L"foo bar:--");
}

void test_trimBack()
{
    JT_EQUAL(trimBack(L" \n\t foo bar \f\r" UTF16_PARAGRAPH_SEPARATOR),
             L" \n\t foo bar");
    JT_EQUAL(trimBack(L":--." UTF16_GREEK_SMALL_SIGMA L"foo bar:--",
                      Unicode::isPunctuation),
             L":--." UTF16_GREEK_SMALL_SIGMA L"foo bar");
}

void test_upper()
{
    JT_EQUAL(upper(L"aBc" UTF16_GREEK_SMALL_SIGMA L"D"),
             L"ABC" UTF16_GREEK_CAPITAL_SIGMA L"D");
}

JT_SUBTEST("Utf16",
           test_append,
           test_caseInsensitiveCompare,
           test_caseInsensitiveEqual,
           test_caseInsensitiveLess,
           test_contains,
           test_endsWith,
           test_findSubstring,
           test_insert,
           test_insertChar,
           test_insertInPlace,
           test_isAlphaNumeric,
           test_isValidUtf16,
           test_join,
           test_lower,
           test_nthCharacter,
           test_replace_indexes,
           test_replace_string,
           test_replaceCodePoint,
           test_replaceInPlace,
           test_replaceInvalidUtf16,
           test_replaceInvalidUtf16InPlace,
           test_reverse,
           test_split_caseInsensitive,
           test_split_whitespace,
           test_splitIf,
           test_splitLines,
           test_startsWith,
           test_stringLength,
           test_substring,
           test_title,
           test_toUtf16,
           test_trim,
           test_trimFront,
           test_trimBack,
           test_upper);
}
