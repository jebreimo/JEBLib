#ifndef JEBSTRING_PATHS_WINDOWSPATHTOKENIZER_HPP
#define JEBSTRING_PATHS_WINDOWSPATHTOKENIZER_HPP

#include "JEBBase/Ranges/Range.hpp"
#include "PathTokenType.hpp"

namespace JEBIO {

using JEBBase::Ranges::Range;

class WindowsPathTokenizer
{
public:
    template <typename It>
    static std::pair<Range<It>, PathTokenType> next(Range<It>& range);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prev(Range<It>& range);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> nextSubToken(Range<It>& range);
    template <typename It>
    static std::pair<Range<It>, PathTokenType> prevSubToken(Range<It>& range);
};

}

#include "WindowsPathTokenizer.impl.hpp"

#endif
