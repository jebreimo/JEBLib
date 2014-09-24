#ifndef JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP
#define JEBSTRING_PATHS_UNIXPATHTOKENIZER_HPP

#include "JEBBase/Ranges/Range.hpp"

namespace JEBString { namespace Paths {

enum class PathTokenType
{
    Empty,
    Root,
    Name,
    PathSeparator,
    ExtensionSeparator
};

class UnixPathTokenizer
{
public:
    template <typename It>
    static std::pair<Range<It>, PathTokenType> next(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prev(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> nextSubToken(Range<It>& path);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prevSubToken(Range<It>& path);
private:
    template <typename It>
    static std::pair<Range<It>, PathTokenType> makeNextResult(
            Range<It>& r, It pos, PathTokenType tokenType);
};

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::next(Range<It>& path)
{
    if (empty(path))
        return makeRange(path, PathTokenType::Empty);

    auto it = find(path, '/');
    if (it == path.end())
        return makeNextResult(path, it, PathTokenType::Name);
    else if (it == path.begin())
        return makeNextResult(path, ++it, PathTokenType::PathSeparator);
    else
        return makeNextResult(path, it, PathTokenType::Name);
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prev(Range<It>& path)
{
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::nextSubToken(Range<It>& path)
{
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::prevSubToken(Range<It>& path)
{
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::makeNextResult(
        Range<It>& r, It pos, PathTokenType tokenType)
{
    auto result = make_range(r.begin(), pos);
    r.setBegin(pos);
    return std::make_pair(result, tokenType);
}

}}

#endif
