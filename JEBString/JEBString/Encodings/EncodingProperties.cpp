#include "EncodingProperties.hpp"

#include <cassert>
#include <cstring>
#include <functional>

namespace JEBString { namespace Encodings {

EncodingProperties::EncodingProperties()
    : m_Endianness(JEBBase::Bits::UnknownEndianness),
      m_MinCharLength(0),
      m_MaxCharLength(0),
      m_Encoding(Encoding::Unknown),
      m_UnitSize(0)
{
}

EncodingProperties::EncodingProperties(Encoding_t encoding,
                                       const std::string& name,
                                       const std::string& byteOrderMark,
                                       Endianness endianness,
                                       size_t unitSize,
                                       size_t minCharLength,
                                       size_t maxCharLength)
    : m_ByteOrderMark(byteOrderMark),
      m_Endianness(endianness),
      m_MinCharLength(minCharLength),
      m_MaxCharLength(maxCharLength),
      m_Name(name),
      m_Encoding(encoding),
      m_UnitSize(unitSize)
{
}

const std::string& EncodingProperties::byteOrderMark() const
{
    return m_ByteOrderMark;
}

void EncodingProperties::setByteOrderMark(const std::string& byteOrderMark)
{
    m_ByteOrderMark = byteOrderMark;
}

Endianness EncodingProperties::endianness() const
{
    return m_Endianness;
}

void EncodingProperties::setEndianness(Endianness endianness)
{
    m_Endianness = endianness;
}

size_t EncodingProperties::minCharLength() const
{
    return m_MinCharLength;
}

void EncodingProperties::setMinCharLength(size_t minCharLength)
{
    m_MinCharLength = minCharLength;
}

size_t EncodingProperties::maxCharLength() const
{
    return m_MaxCharLength;
}

void EncodingProperties::setMaxCharLength(size_t maxCharLength)
{
    m_MaxCharLength = maxCharLength;
}

const std::string& EncodingProperties::name() const
{
    return m_Name;
}

void EncodingProperties::setName(const std::string& name)
{
    m_Name = name;
}

Encoding_t EncodingProperties::encoding() const
{
    return m_Encoding;
}

void EncodingProperties::setEncoding(Encoding_t encoding)
{
    m_Encoding = encoding;
}

size_t EncodingProperties::unitSize() const
{
    return m_UnitSize;
}

void EncodingProperties::setUnitSize(size_t unitSize)
{
    m_UnitSize = unitSize;
}

}}
