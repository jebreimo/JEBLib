#include "JEBBase/Ranges/RangeAlgorithms.hpp"

namespace JEBIO {

using JEBBase::Ranges::makeRange;
using std::make_pair;

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::next(
        Range<It>& path)
{
    if (empty(path))
        return make_pair(path, PathTokenType::Empty);

    auto it = findFirstOf(path, makeRange("\\:"));
    if (it == end(path))
        return make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != begin(path))
        return make_pair(takeHead(path, it), PathTokenType::Name);
    else if (*it == '\\')
        return make_pair(takeHead(path, ++it), PathTokenType::DirSeparator);
    else
        return make_pair(takeHead(path, ++it), PathTokenType::DriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prev(
        Range<It>& path)
{
    if (empty(path))
        return make_pair(path, PathTokenType::Empty);

    auto it = findLastOf(path, makeRange("\\:"));
    if (*it != '\\' && *it != ':')
        return make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return make_pair(takeTail(path, it), PathTokenType::Name);
    else if (*--it == '\\')
        return make_pair(takeTail(path, it), PathTokenType::DirSeparator);
    else
        return make_pair(takeTail(path, it), PathTokenType::DriveSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::nextSubToken(
        Range<It>& path)
{
    if (empty(path))
        return make_pair(path, PathTokenType::Empty);

    auto it = findFirstOf(path, makeRange("\\:."));
    if (it == end(path))
        return make_pair(takeHead(path, it), PathTokenType::Name);
    else if (it != begin(path))
        return make_pair(takeHead(path, it), PathTokenType::Name);
    else if (*it == '\\')
        return make_pair(takeHead(path, ++it), PathTokenType::DirSeparator);
    else if (*it == ':')
        return make_pair(takeHead(path, ++it), PathTokenType::DriveSeparator);
    else
        return make_pair(takeHead(path, ++it),
                         PathTokenType::ExtensionSeparator);
}

template <typename It>
std::pair<Range<It>, PathTokenType> WindowsPathTokenizer::prevSubToken(
        Range<It>& path)
{
    if (empty(path))
        return make_pair(path, PathTokenType::Empty);

    auto it = findLastOf(path, makeRange("\\:."));
    if (*it != '\\' && *it != ':' && *it != '.')
        return make_pair(takeTail(path, it), PathTokenType::Name);
    else if (++it != end(path))
        return make_pair(takeTail(path, it), PathTokenType::Name);
    else if (*--it == '\\')
        return make_pair(takeTail(path, it), PathTokenType::DirSeparator);
    else if (*it == ':')
        return make_pair(takeTail(path, it), PathTokenType::DriveSeparator);
    else
        return make_pair(takeTail(path, it),
                         PathTokenType::ExtensionSeparator);
}

}
