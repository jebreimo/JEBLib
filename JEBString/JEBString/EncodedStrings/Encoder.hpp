#ifndef JEBSTRING_ENCODEDSTRINGS_ENCODER_HPP
#define JEBSTRING_ENCODEDSTRINGS_ENCODER_HPP

#include "Encoding.hpp"

namespace JEBString { namespace EncodedStrings {

template <typename OutIt, typename Enc>
class Encoder
{
public:
    typedef OutIt Iterator;
    typedef Enc Encoding;

    Encoder(OutIt dst, Encoding encoding)
        : m_Destination(dst),
          m_Encoding(encoding)
    {}

    void encode(uint32_t codePoint)
    {
        m_Encoding.encodeCodePoint(m_Destination, codePoint);
    }

    Encoding encoding() const
    {
        return m_Encoding;
    }

    OutIt iterator() const
    {
        return m_Destination;
    }
private:
    OutIt m_Destination;
    Encoding m_Encoding;
};

}}

#endif
