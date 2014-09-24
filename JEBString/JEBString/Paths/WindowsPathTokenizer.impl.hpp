#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBString { namespace Paths {

using JEBBase::Ranges::makeRange;

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::next(
        Range<It>& str)
{
    if (empty(path))
        return makeRange(path, PathTokenType::Empty);

    auto it = find_if(begin(str), end(str),
                      [](auto c){return c == '\\' || c == ':'});
    if (it == path.end())
        return makeNextResult(path, it, PathTokenType::Name);
    else if (it == path.begin())
    {
        if (*it == '\\')
            return makeNextResult(path, ++it, PathTokenType::PathSeparator);
        else
            return makeNextResult(path, ++it, PathTokenType::Invalid);
    }
    else
        return makeNextResult(path, it, PathTokenType::Name);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prev(
        Range<It>& range)
{
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::nextSubToken(
        Range<It>& range)
{
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prevSubToken(
        Range<It>& range)
{
    return std::pair<Range<It>, PathTokenType>();
}

}}
