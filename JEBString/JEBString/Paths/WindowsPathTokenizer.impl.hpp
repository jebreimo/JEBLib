#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBString { namespace Paths {

using JEBBase::Ranges::makeRange;

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::next(
        Range<It>& path)
{
    if (empty(path))
        return makeRange(path, PathTokenType::Empty);

    auto it = find_if(begin(path), end(path),
                      [](auto c){return c == '\\' || c == ':';});
    if (it == end(path))
    {
        return makeNextResult(path, it, PathTokenType::Name);
    }
    else if (it == begin(path))
    {
        if (*it == '\\')
            return makeNextResult(path, ++it, PathTokenType::PathSeparator);
        else
            return makeNextResult(path, ++it, PathTokenType::Invalid);
    }
    else if (it == '\\')
    {
        return makeNextResult(path, it, PathTokenType::Name);
    }
    else if (std::distance(begin(path), it) == 1 && *begin(path))
    {

    }
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
