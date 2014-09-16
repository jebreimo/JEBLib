#ifndef JEB_STRING_PREDICATES_HPP
#define JEB_STRING_PREDICATES_HPP

#include <algorithm>
#include <functional>
#include <cstdint>
#include "JEB/Unicode/CharClass.hpp"

namespace JEB { namespace String {

// class CharClassPredicate : public std::unary_function<uint32_t, bool>
// {
// public:
//     CharClassPredicate(uint32_t classes);
//     bool operator()(uint32_t chr) const;
// private:
//     uint32_t m_Classes;
// };

template <typename BinaryFunc = std::equal_to<uint32_t>>
class CharacterPredicate : public std::unary_function<uint32_t, bool>
{
public:
    CharacterPredicate(uint32_t chr, BinaryFunc compare)
        : m_Chr(chr),
          m_Compare(compare)
    {}

    bool operator()(uint32_t chr) const {return m_Compare(chr, m_Chr);}
private:
    uint32_t m_Chr;
    BinaryFunc m_Compare;
};

// class HexDigitPredicate
// {
// public:
//     bool operator()(uint32_t chr);
// };

// class NewlinePredicate : public std::unary_function<uint32_t, bool>
// {
// public:
//     bool operator()(uint32_t chr) const;
// private:
//     static uint32_t s_CodePoints[7];
// };

template <typename FwdIt, typename BinaryFunc = std::equal_to<uint32_t>>
class OneOfPredicate;

template <typename FwdIt, typename BinaryFunc>
OneOfPredicate<FwdIt, BinaryFunc>
    isOneOf(FwdIt begin, FwdIt end, BinaryFunc compare);

template <typename FwdIt>
OneOfPredicate<FwdIt> isOneOf(FwdIt begin, FwdIt end);

template <typename FwdIt, typename BinaryFunc>
class OneOfPredicate : public std::unary_function<uint32_t, bool>
{
public:
    OneOfPredicate(const OneOfPredicate& other)
        : m_Begin(other.m_Begin),
          m_End(other.m_End),
          m_Compare(other.m_Compare)
    {
    }

    OneOfPredicate(OneOfPredicate&& other)
    {
        std::swap(m_Begin, other.m_Begin);
        std::swap(m_End, other.m_End);
        std::swap(m_Compare, other.m_Compare);
    }

    bool operator()(uint32_t chr)
    {
        for (FwdIt it = m_Begin; it != m_End; ++it)
            if (m_Compare(*it, chr))
                return true;
        return false;
    }
private:
    OneOfPredicate(FwdIt begin, FwdIt end, BinaryFunc compare)
        : m_Begin(begin),
          m_End(end),
          m_Compare(compare)
    {}
    OneOfPredicate(FwdIt begin, FwdIt end)
        : m_Begin(begin),
          m_End(end),
          m_Compare(BinaryFunc())
    {}

    friend OneOfPredicate<FwdIt, BinaryFunc>
        isOneOf<FwdIt, BinaryFunc>(FwdIt begin, FwdIt end, BinaryFunc compare);
    friend OneOfPredicate<FwdIt, std::equal_to<uint32_t>>
        isOneOf<FwdIt>(FwdIt begin, FwdIt end);

    FwdIt m_Begin;
    FwdIt m_End;
    BinaryFunc m_Compare;
};

// class WhitespacePredicate : public std::unary_function<uint32_t, bool>
// {
// public:
//     bool operator()(uint32_t chr) const;
// private:
//     static uint32_t s_CodePoints[12];
// };

// CharClassPredicate isCharClass(uint32_t classes);
// bool isCharClass(uint32_t classes, uint32_t chr);

// CharClassPredicate isAlphaNumeric();
// bool isAlphaNumeric(uint32_t chr);

// CharClassPredicate isCasedLetter();
// bool isCasedLetter(uint32_t chr);

template <typename BinaryFunc>
CharacterPredicate<BinaryFunc> isCharacter(uint32_t chr, BinaryFunc compare)
{
    return CharacterPredicate<BinaryFunc>(chr, compare);
}

inline CharacterPredicate<> isCharacter(uint32_t chr)
{
    return CharacterPredicate<>(chr, std::equal_to<uint32_t>());
}

// CharClassPredicate isGraphical();
// bool isGraphical(uint32_t chr);

// HexDigitPredicate isHexDigit();
// bool isHexDigit(uint32_t chr);

// CharClassPredicate isLetter();
// bool isLetter(uint32_t chr);

// CharClassPredicate isLower();
// bool isLower(uint32_t chr);

// NewlinePredicate isNewline();
// bool isNewline(uint32_t chr);

// CharClassPredicate isNumber();
// bool isNumber(uint32_t chr);

template <typename FwdIt, typename BinaryFunc>
OneOfPredicate<FwdIt, BinaryFunc>
    isOneOf(FwdIt begin, FwdIt end, BinaryFunc compare)
{
    return OneOfPredicate<FwdIt, BinaryFunc>(begin, end, compare);
}

template <typename FwdIt>
OneOfPredicate<FwdIt> isOneOf(FwdIt begin, FwdIt end)
{
    return OneOfPredicate<FwdIt>(begin, end);
}

// CharClassPredicate isTitle();
// bool isTitle(uint32_t chr);

// CharClassPredicate isUpper();
// bool isUpper(uint32_t chr);

// CharClassPredicate isVisible();
// bool isVisible(uint32_t chr);

// WhitespacePredicate isWhitespace();
// bool isWhitespace(uint32_t chr);

}}

#endif
