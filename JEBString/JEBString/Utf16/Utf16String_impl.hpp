#include "JEBString/EncodedStrings/EncodedString.hpp"
#include "JEBString/RawStrings/RawString.hpp"
#include "Utf16Utilities.hpp"

namespace JEBString { namespace Utf16 {

template <typename FwdIt>
std::wstring& appendJoin(std::wstring& dst, FwdIt first, FwdIt last)
{
    return RawStrings::appendJoin(dst, first, last);
}

template <typename FwdIt>
std::wstring& appendJoin(std::wstring& dst, FwdIt first, FwdIt last,
                         const std::wstring& delimiter)
{
    return RawStrings::appendJoin(dst, first, last, delimiter);
}

template <typename FwdIt>
bool isAlphaNumeric(FwdIt first, FwdIt last)
{
    return EncodedStrings::isAlphaNumeric(utf16Range(first, last));
}

template <typename FwdIt>
std::wstring join(FwdIt first, FwdIt last)
{
    return RawStrings::join<std::wstring>(first, last);
}

template <typename FwdIt>
std::wstring join(FwdIt first, FwdIt last, const std::wstring& separator)
{
    return RawStrings::join<std::wstring>(first, last, separator);
}

template <typename UnaryPred>
std::vector<std::wstring> splitIf(
        const std::wstring& str,
        UnaryPred delimiterPredicate,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::wstring> parts;
    EncodedStrings::forEachToken(utf16Range(str), delimiterPredicate,
                          rangePushBacker(parts), maxParts, flags);
    return parts;
}

template <typename FwdIt>
size_t stringLength(FwdIt first, FwdIt last)
{
    return EncodedStrings::stringLength(utf16Range(first, last));
}

template <typename UnaryPred>
std::wstring trim(const std::wstring& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trim(utf16Range(str), predicate));
}

template <typename UnaryPred>
std::wstring trimFront(const std::wstring& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trimFront(utf16Range(str), predicate));
}

template <typename UnaryPred>
std::wstring trimBack(const std::wstring& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trimBack(utf16Range(str), predicate));
}

}}
