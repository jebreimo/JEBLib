#ifndef JEBSTRING_CODEPOINTS_CODEPOINTITERATOR_HPP
#define JEBSTRING_CODEPOINTS_CODEPOINTITERATOR_HPP

#include <stdexcept>
#include "JEBString/JEBStringFlags.hpp"
#include "JEBString/EncodedStrings/EncodedRange.hpp"
#include "JEBString/EncodedStrings/ForwardDecoder.hpp"
#include "JEBString/EncodedStrings/ReverseDecoder.hpp"

namespace JEBString { namespace CodePoints {

using JEBString::EncodedStrings::EncodedRange;
using JEBString::EncodedStrings::ForwardDecoder;
using JEBString::EncodedStrings::ReverseDecoder;

template <typename Decoder>
class CodePointIterator
{
public:
    typedef typename Decoder::Iterator Iterator;
    typedef typename Decoder::Encoding Encoding;
    static const bool Forward = Decoder::Forward;

    CodePointIterator()
    {}

    CodePointIterator(Iterator first, Iterator last, Decoder decoder)
        : m_First(first),
          m_Last(last),
          m_Decoder(decoder)
    {}

    bool next(uint32_t& chr)
    {
        switch (m_Decoder.next(chr, m_First, m_Last))
        {
            case DecodeResult::EndOfString:
                return false;
            case DecodeResult::Incomplete:
                throw std::logic_error("Incomplete character.");
            case DecodeResult::Invalid:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    bool next()
    {
        uint32_t ch;
        return next(ch);
    }

    Iterator internalBegin() const
    {
        return Forward ? m_First : m_Last;
    }

    void setInternalBegin(Iterator it)
    {
        if (Forward)
            m_First = it;
        else
            m_Last = it;
    }

    Iterator internalEnd() const
    {
        return Forward ? m_Last : m_First;
    }

    void setInternalEnd(Iterator it)
    {
        if (Forward)
            m_Last = it;
        else
            m_First = it;
    }

    Iterator begin() const
    {
        return m_First;
    }

    void setBegin(Iterator it)
    {
        m_First = it;
    }

    Iterator end() const
    {
        return m_Last;
    }

    void setEnd(Iterator it)
    {
        m_Last = it;
    }

    Encoding encoding() const
    {
        return m_Decoder.encoding();
    }
private:
    Iterator m_First;
    Iterator m_Last;
    Decoder m_Decoder;
};

template <typename Decoder>
typename Decoder::Iterator begin(const CodePointIterator<Decoder>& it)
{
    return it.begin();
}

template <typename Decoder>
typename Decoder::Iterator begin(CodePointIterator<Decoder>& it)
{
    return it.begin();
}

template <typename Decoder>
typename Decoder::Iterator end(const CodePointIterator<Decoder>& it)
{
    return it.end();
}

template <typename Decoder>
typename Decoder::Iterator end(CodePointIterator<Decoder>& it)
{
    return it.end();
}

template <typename Decoder>
bool empty(const CodePointIterator<Decoder>& it)
{
    return begin(it) == end(it);
}

template <typename Iterator, typename Encoding>
CodePointIterator<ForwardDecoder<Iterator, Encoding>>
    makeForwardIterator(Iterator first, Iterator last, Encoding encoding)
{
    return CodePointIterator<ForwardDecoder<Iterator, Encoding>>(
            first, last, ForwardDecoder<Iterator, Encoding>(encoding));
}

template <typename Iterator, typename Encoding>
CodePointIterator<ForwardDecoder<Iterator, Encoding>>
    makeForwardIterator(EncodedRange<Iterator, Encoding> range)
{
    return makeForwardIterator(begin(range), end(range), range.encoding());
}

template <typename Iterator, typename Encoding>
CodePointIterator<ReverseDecoder<Iterator, Encoding>>
    makeReverseIterator(Iterator first, Iterator last, Encoding encoding)
{
    return CodePointIterator<ReverseDecoder<Iterator, Encoding>>(
            first, last, ReverseDecoder<Iterator, Encoding>(encoding));
}

template <typename Iterator, typename Encoding>
CodePointIterator<ReverseDecoder<Iterator, Encoding>>
    makeReverseIterator(EncodedRange<Iterator, Encoding> range)
{
    return makeReverseIterator(begin(range), end(range), range.encoding());
}

template <typename Decoder>
EncodedRange<typename Decoder::Iterator, typename Decoder::Encoding>
    makeEncodedRange(CodePointIterator<Decoder> it)
{
    using JEBString::EncodedStrings::makeEncodedRange;
    return makeEncodedRange(begin(it), end(it), it.encoding());
}

}}

#endif
