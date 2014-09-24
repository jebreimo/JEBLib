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
    static std::pair<Range<It>, PathTokenType> makeResult(
            Range<It>& r, It pos, PathTokenType tokenType);
};

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::next(Range<It>& path)
{
    auto it = find(path, '/');
    return std::pair<Range<It>, PathTokenType>();
}

template <typename It>
std::pair<Range<It>, PathTokenType> UnixPathTokenizer::makeResult(
        Range<It>& r, It pos, PathTokenType tokenType)
{
    return std::pair<Range<It>, PathTokenType>();
}

}}

#endif
