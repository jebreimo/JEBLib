#ifndef JEBSTRING_ENCODEDSTRINGS_REVERSEDECODER_HPP
#define JEBSTRING_ENCODEDSTRINGS_REVERSEDECODER_HPP

#include "Encoding.hpp"

namespace JEBString { namespace EncodedStrings {

template <typename BiIt, typename Enc>
class ReverseDecoder
{
public:
    typedef BiIt Iterator;
    typedef Enc Encoding;
    static const bool Forward = false;

    ReverseDecoder(Encoding encoding) : m_Encoding(encoding)
    {}

    unsigned next(uint32_t& codePoint, BiIt begin, BiIt& it)
    {
        return m_Encoding.prevCodePoint(codePoint, begin, it);
    }

    Encoding encoding() const
    {
        return m_Encoding;
    }
private:
    Encoding m_Encoding;
};

}}

#endif
