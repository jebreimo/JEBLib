#include "JEBString/EncodedStrings/Encoder.hpp"
#include "JEBString/EncodedStrings/EncodedRange.hpp"
#include "JEBString/EncodedStrings/Utf8Encoding.hpp"

namespace JEBString { namespace Utf8 {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::Utf8Encoding;

template <typename It>
EncodedRange<It, Utf8Encoding> utf8Range(It begin, It end)
{
    return makeEncodedRange(begin, end, Utf8Encoding());
}

inline EncodedRange<std::string::const_iterator, Utf8Encoding>
    utf8Range(const std::string& str)
{
    return makeEncodedRange(str, Utf8Encoding());
}

inline EncodedRange<std::string::iterator, Utf8Encoding>
    utf8Range(std::string& str)
{
    return makeEncodedRange(str, Utf8Encoding());
}

inline std::string toString(
        EncodedRange<std::string::const_iterator, Utf8Encoding> range)
{
    return std::string(begin(range), end(range));
}

inline std::string toString(
        EncodedRange<std::string::iterator, Utf8Encoding> range)
{
    return std::string(begin(range), end(range));
}

template <typename OutIt>
EncodedStrings::Encoder<OutIt, Utf8Encoding> utf8Encoder(OutIt it)
{
    return EncodedStrings::Encoder<OutIt, Utf8Encoding>(it, Utf8Encoding());
}

inline EncodedStrings::Encoder<std::back_insert_iterator<std::string>,
                               Utf8Encoding>
    utf8Encoder(std::string& str)
{
    return utf8Encoder(std::back_inserter(str));
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
