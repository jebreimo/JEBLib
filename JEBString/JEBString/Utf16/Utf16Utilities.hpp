#include "JEBString/EncodedStrings/Encoder.hpp"
#include "JEBString/EncodedStrings/EncodedRange.hpp"
#include "JEBString/EncodedStrings/Utf16Encoding.hpp"

namespace JEBString { namespace Utf16 {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::Utf16Encoding;

template <typename It>
EncodedRange<It, Utf16Encoding> utf16Range(It begin, It end)
{
    return makeEncodedRange(begin, end, Utf16Encoding());
}

inline EncodedRange<std::wstring::const_iterator, Utf16Encoding>
    utf16Range(const std::wstring& str)
{
    return utf16Range(begin(str), end(str));
}

inline EncodedRange<std::wstring::iterator, Utf16Encoding>
    utf16Range(std::wstring& str)
{
    return utf16Range(begin(str), end(str));
}

inline std::wstring toString(
        EncodedRange<std::wstring::const_iterator, Utf16Encoding> range)
{
    return std::wstring(begin(range), end(range));
}

inline std::wstring toString(
        EncodedRange<std::wstring::iterator, Utf16Encoding> range)
{
    return std::wstring(begin(range), end(range));
}

template <typename OutIt>
EncodedStrings::Encoder<OutIt, Utf16Encoding> utf16Encoder(OutIt it)
{
    return EncodedStrings::Encoder<OutIt, Utf16Encoding>(it, Utf16Encoding());
}

inline EncodedStrings::Encoder<std::back_insert_iterator<std::wstring>,
                          Utf16Encoding>
    utf16Encoder(std::wstring& str)
{
    return utf16Encoder(std::back_inserter(str));
}

template <typename Container>
struct RangePushBacker
{
    typedef typename Container::value_type Value;

    RangePushBacker(Container& container)
        : m_Container(container)
    {}

    template <typename Iterator, typename Encoding>
    void operator()(EncodedRange<Iterator, Encoding> range)
    {
        m_Container.push_back(Value(begin(range), end(range)));
    }

    Container& m_Container;
};

template <typename Container>
RangePushBacker<Container> rangePushBacker(Container& container)
{
    return RangePushBacker<Container>(container);
}

}}
