#ifndef JEBSTRING_ENCODEDSTRINGS_ENCODEDRANGE_HPP
#define JEBSTRING_ENCODEDSTRINGS_ENCODEDRANGE_HPP

#include <cstring>
#include <cwchar>

namespace JEBString { namespace EncodedStrings {

template <typename Iterator, typename EncodingType>
class EncodedRange
{
public:
    typedef EncodingType Encoding;

    EncodedRange();
    EncodedRange(Iterator first, Iterator last, Encoding encoding);

    Iterator begin() const;
    void setBegin(Iterator first);

    Iterator end() const;
    void setEnd(Iterator last);

    Encoding encoding() const;
private:
    Iterator m_First;
    Iterator m_Last;
    Encoding m_Encoding;
};

template <typename Iterator, typename Encoding>
EncodedRange<Iterator, Encoding>::EncodedRange()
{}

template <typename Iterator, typename Encoding>
EncodedRange<Iterator, Encoding>::EncodedRange(Iterator first, Iterator last,
                                               Encoding encoding)
    : m_First(first),
      m_Last(last),
      m_Encoding(encoding)
{}

template <typename Iterator, typename Encoding>
Iterator EncodedRange<Iterator, Encoding>::begin() const
{
    return m_First;
}

template <typename Iterator, typename Encoding>
void EncodedRange<Iterator, Encoding>::setBegin(Iterator first)
{
    m_First = first;
}

template <typename Iterator, typename Encoding>
Iterator EncodedRange<Iterator, Encoding>::end() const
{
    return m_Last;
}

template <typename Iterator, typename Encoding>
void EncodedRange<Iterator, Encoding>::setEnd(Iterator last)
{
    m_Last = last;
}

template <typename Iterator, typename Encoding>
Encoding EncodedRange<Iterator, Encoding>::encoding() const
{
    return m_Encoding;
}

template <typename Iterator, typename Encoding>
Iterator begin(EncodedRange<Iterator, Encoding> range)
{
    return range.begin();
}

template <typename Iterator, typename Encoding>
Iterator end(EncodedRange<Iterator, Encoding> range)
{
    return range.end();
}

template <typename Iterator, typename Encoding>
bool empty(EncodedRange<Iterator, Encoding> range)
{
    return begin(range) == end(range);
}

template <typename Iterator, typename Encoding>
EncodedRange<Iterator, Encoding> makeEncodedRange(
        Iterator first, Iterator last, Encoding encoding)
{
    return EncodedRange<Iterator, Encoding>(first, last, encoding);
}

template <typename Container, typename Encoding>
EncodedRange<typename Container::iterator, Encoding> makeEncodedRange(
        Container& container, Encoding encoding)
{
    return makeEncodedRange(begin(container), end(container), encoding);
}

template <typename Container, typename Encoding>
EncodedRange<typename Container::const_iterator, Encoding> makeEncodedRange(
        const Container& container, Encoding encoding)
{
    return makeEncodedRange(begin(container), end(container), encoding);
}

template <size_t N, typename Encoding>
EncodedRange<const char*, Encoding> makeEncodedRange(
        const char (&str)[N], Encoding encoding)
{
    if (!str[N - 1])
        return makeEncodedRange(&str[0], &str[N - 1], encoding);
    else
        return makeEncodedRange(&str[0], &str[N], encoding);
}

template <size_t N, typename Encoding>
EncodedRange<const wchar_t*, Encoding> makeEncodedRange(
        const wchar_t (&str)[N], Encoding encoding)
{
    if (!str[N - 1])
        return makeEncodedRange(&str[0], &str[N - 1], encoding);
    else
        return makeEncodedRange(&str[0], &str[N], encoding);
}

template <typename Encoding>
EncodedRange<const char*, Encoding> makeEncodedStringRange(
        const char* str, Encoding encoding)
{
    if (!str)
        return makeEncodedRange(str, str, encoding);
    else
        return makeEncodedRange(str, str + std::strlen(str), encoding);
}

template <typename Encoding>
EncodedRange<char*, Encoding> makeEncodedStringRange(
        char* str, Encoding encoding)
{
    if (!str)
        return makeEncodedRange(str, str, encoding);
    else
        return makeEncodedRange(str, str + std::strlen(str), encoding);
}

template <typename Encoding>
EncodedRange<const wchar_t*, Encoding> makeEncodedStringRange(
        const wchar_t* str, Encoding encoding)
{
    if (!str)
        return makeEncodedRange(str, str, encoding);
    else
        return makeEncodedRange(str, str + std::wcslen(str), encoding);
}

template <typename Encoding>
EncodedRange<wchar_t*, Encoding> makeEncodedStringRange(
        wchar_t* str, Encoding encoding)
{
    if (!str)
        return makeEncodedRange(str, str, encoding);
    else
        return makeEncodedRange(str, str + std::wcslen(str), encoding);
}

}}

#endif
