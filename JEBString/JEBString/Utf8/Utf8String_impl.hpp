#include "JEBString/EncodedStrings/EncodedString.hpp"
#include "JEBString/RawStrings/RawString.hpp"
#include "Utf8Utilities.hpp"

namespace JEBString { namespace Utf8 {

template <typename FwdIt>
std::string& appendJoin(std::string& dst, FwdIt first, FwdIt last)
{
    return RawStrings::appendJoin(dst, first, last);
}

template <typename FwdIt>
std::string& appendJoin(std::string& dst, FwdIt first, FwdIt last,
                        const std::string& delimiter)
{
    return RawStrings::appendJoin(dst, first, last, delimiter);
}

template <typename FwdIt>
bool isAlphaNumeric(FwdIt first, FwdIt last)
{
    return EncodedStrings::isAlphaNumeric(utf8Range(first, last));
}

template <typename FwdIt>
std::string join(FwdIt first, FwdIt last)
{
    return RawStrings::join<std::string>(first, last);
}

template <typename FwdIt>
std::string join(FwdIt first, FwdIt last, const std::string& separator)
{
    return RawStrings::join<std::string>(first, last, separator);
}

template <typename UnaryPred>
std::vector<std::string> splitIf(
        const std::string& str,
        UnaryPred delimiterPredicate,
        size_t maxParts /*= 0*/,
        SplitFlags_t flags /*= SplitFlags::Defaults*/)
{
    std::vector<std::string> parts;
    EncodedStrings::forEachToken(utf8Range(str), delimiterPredicate,
                                 rangePushBacker(parts), maxParts, flags);
    return parts;
}

template <typename FwdIt>
size_t stringLength(FwdIt first, FwdIt last)
{
    return EncodedStrings::stringLength(utf8Range(first, last));
}

template <typename UnaryPred>
std::string trim(const std::string& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trim(utf8Range(str), predicate));
}

template <typename UnaryPred>
std::string trimFront(const std::string& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trimFront(utf8Range(str), predicate));
}

template <typename UnaryPred>
std::string trimBack(const std::string& str, UnaryPred predicate)
{
    return toString(EncodedStrings::trimBack(utf8Range(str), predicate));
}

}}
