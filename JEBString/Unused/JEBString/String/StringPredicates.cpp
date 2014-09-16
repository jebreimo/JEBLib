#include "StringPredicates.hpp"
#include "JEB/Unicode/CaseConverter.hpp"
#include "JEB/Unicode/CharClass.hpp"
#include "JEB/Unicode/UnicodeChars.hpp"

namespace JEB { namespace String {

// CharClassPredicate::CharClassPredicate(uint32_t classes)
//     : m_Classes(classes)
// {}

// bool CharClassPredicate::operator()(uint32_t chr) const
// {
//     return (Unicode::charClass(chr) & m_Classes) != 0;
// }

// uint32_t NewlinePredicate::s_CodePoints[7] = {
//     '\n',
//     '\v',
//     '\f',
//     '\r',
//     Unicode::NextLine,
//     Unicode::LineSeparator,
//     Unicode::ParagraphSeparator
// };

// bool NewlinePredicate::operator()(uint32_t chr) const
// {
//     return std::binary_search(std::begin(s_CodePoints),
//                               std::end(s_CodePoints),
//                               chr);
// }

// NewlinePredicate isNewline()
// {
//     return NewlinePredicate();
// }

// bool isNewline(uint32_t chr)
// {
//     return isNewline()(chr);
// }

// bool HexDigitPredicate::operator()(uint32_t chr)
// {
//     return ('0' <= chr && chr <= '9') ||
//            ('A' <= chr && chr <= 'F') ||
//            ('a' <= chr && chr <= 'f');
// }

// HexDigitPredicate isHexDigit()
// {
//     return HexDigitPredicate();
// }

// bool isHexDigit(uint32_t chr)
// {
//     return isHexDigit()(chr);
// }

// uint32_t WhitespacePredicate::s_CodePoints[12] = {
//     '\t',
//     '\n',
//     '\v',
//     '\f',
//     '\r',
//     ' ',
//     Unicode::NextLine,
//     Unicode::ZeroWidthSpace,
//     Unicode::LineSeparator,
//     Unicode::ParagraphSeparator,
//     Unicode::MediumMathematicalSpace,
//     Unicode::IdeographicSpace
// };

// bool WhitespacePredicate::operator()(uint32_t chr) const
// {
//     return std::binary_search(std::begin(s_CodePoints),
//                               std::end(s_CodePoints),
//                               chr);
// }

// WhitespacePredicate isWhitespace()
// {
//     return WhitespacePredicate();
// }

// bool isWhitespace(uint32_t chr)
// {
//     return isWhitespace()(chr);
// }

// CharClassPredicate isCharClass(uint32_t classes)
// {
//     return CharClassPredicate(classes);
// }

// bool isCharClass(uint32_t classes, uint32_t chr)
// {
//     return isCharClass(classes)(chr);
// }

// CharClassPredicate isAlphaNumeric()
// {
//     return CharClassPredicate(Unicode::CharClass::Letter |
//                               Unicode::CharClass::Number);
// }

// bool isAlphaNumeric(uint32_t chr)
// {
//     return isAlphaNumeric()(chr);
// }

// CharClassPredicate isCasedLetter()
// {
//     return CharClassPredicate(Unicode::CharClass::CasedLetter);
// }

// bool isCasedLetter(uint32_t chr)
// {
//     return isCasedLetter()(chr);
// }

// CharClassPredicate isGraphical()
// {
//     return CharClassPredicate(Unicode::CharClass::Letter |
//                               Unicode::CharClass::Mark |
//                               Unicode::CharClass::Number |
//                               Unicode::CharClass::Punctuation |
//                               Unicode::CharClass::Symbol);
// }

// bool isGraphical(uint32_t chr)
// {
//     return isGraphical()(chr);
// }

// CharClassPredicate isLetter()
// {
//     return CharClassPredicate(Unicode::CharClass::Letter);
// }

// bool isLetter(uint32_t chr)
// {
//     return isLetter()(chr);
// }

// CharClassPredicate isLower()
// {
//     return CharClassPredicate(Unicode::CharClass::LowercaseLetter);
// }

// bool isLower(uint32_t chr)
// {
//     return isLower()(chr);
// }

// CharClassPredicate isNumber()
// {
//     return CharClassPredicate(Unicode::CharClass::Number);
// }

// bool isNumber(uint32_t chr)
// {
//     return isNumber()(chr);
// }

// CharClassPredicate isTitle()
// {
//     return CharClassPredicate(Unicode::CharClass::TitlecaseLetter);
// }

// bool isTitle(uint32_t chr)
// {
//     return isTitle()(chr);
// }

// CharClassPredicate isUpper()
// {
//     return CharClassPredicate(Unicode::CharClass::UppercaseLetter);
// }

// bool isUpper(uint32_t chr)
// {
//     return isUpper()(chr);
// }

// CharClassPredicate isVisible()
// {
//     return CharClassPredicate(Unicode::CharClass::Letter |
//                               Unicode::CharClass::Mark |
//                               Unicode::CharClass::Number |
//                               Unicode::CharClass::Punctuation |
//                               Unicode::CharClass::Symbol |
//                               Unicode::CharClass::Separator);
// }

// bool isVisible(uint32_t chr)
// {
//     return isVisible()(chr);
// }

}}
