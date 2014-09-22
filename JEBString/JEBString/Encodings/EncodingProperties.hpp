#ifndef JEBSTRING_ENCODINGS_ENCODINGPROPERTIES_HPP
#define JEBSTRING_ENCODINGS_ENCODINGPROPERTIES_HPP

#include <string>
#include "JEBBase/Bits/Endian.hpp"
#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace Encodings {

using JEBBase::Bits::Endianness;

class EncodingProperties
{
public:
    EncodingProperties();

    EncodingProperties(Encoding_t encoding,
                       const std::string& name,
                       const std::string& byteOrderMark,
                       Endianness endianness,
                       size_t unitSize,
                       size_t minCharLength,
                       size_t maxCharLength);

    const std::string& byteOrderMark() const;
    void setByteOrderMark(const std::string& byteOrderMark);

    Endianness endianness() const;
    void setEndianness(Endianness endianness);

    size_t minCharLength() const;
    void setMinCharLength(size_t minCharLength);

    size_t maxCharLength() const;
    void setMaxCharLength(size_t maxCharLength);

    const std::string& name() const;
    void setName(const std::string& name);

    Encoding_t encoding() const;
    void setEncoding(Encoding_t encoding);

    size_t unitSize() const;
    void setUnitSize(size_t unitSize);
private:
    std::string m_ByteOrderMark;
    Endianness m_Endianness;
    size_t m_MinCharLength;
    size_t m_MaxCharLength;
    std::string m_Name;
    Encoding_t m_Encoding;
    size_t m_UnitSize;
};

}}

#endif
