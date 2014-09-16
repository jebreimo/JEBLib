#ifndef JEBSTRING_ENCODEDSTRINGS_FORWARDDECODER_HPP
#define JEBSTRING_ENCODEDSTRINGS_FORWARDDECODER_HPP

#include "Encoding.hpp"

namespace JEBString { namespace EncodedStrings {

template <typename FwdIt, typename Enc>
class ForwardDecoder
{
public:
    typedef FwdIt Iterator;
    typedef Enc Encoding;
    static const bool Forward = true;

    ForwardDecoder(Encoding encoding) : m_Encoding(encoding)
    {}

    unsigned next(uint32_t& codePoint, FwdIt& it, FwdIt end)
    {
        return m_Encoding.nextCodePoint(codePoint, it, end);
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
