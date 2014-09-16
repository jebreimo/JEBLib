#include "StringConverter.hpp"
#include <algorithm>
#include "JEBString/Utf8/Utf8Iterators.hpp"
#include "JEBString/Utf16/Utf16Iterators.hpp"
#include "JEBString/Utf16/DecodeUtf16.hpp"
#include "JEBString/Utf16/EncodeUtf16.hpp"

namespace JEBString { namespace Encodings {

typedef unsigned (*NextCodePointFunc)(uint32_t&, const char*&, const char*);
typedef bool (*EncodeFunc)(char*&, char*, uint32_t);

NextCodePointFunc getNextCodePointFunc(Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::Utf8:
        return Utf8::nextUtf8CodePoint<const char*>;
    case Encoding::Utf16LE:
        return  Utf16::nextUtf16LECodePoint<const char*>;
    case Encoding::Utf16BE:
        return  Utf16::nextUtf16BECodePoint<const char*>;
    default:
        throw std::invalid_argument("Unsupported input encoding");
    };
}

EncodeFunc getEncodeFunc(Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::Utf8:
        return Utf8::encodeUtf8<char*>;
    case Encoding::Utf16LE:
        return Utf16::encodeUtf16LE<char*>;
    case Encoding::Utf16BE:
        return Utf16::encodeUtf16BE<char*>;
    default:
        throw std::invalid_argument("Unsupported output encoding");
    };
}

std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                  Encoding_t srcEncoding,
                                  char* dstBuffer, size_t dstSize,
                                  Encoding_t dstEncoding)
{
    // TODO: if source and dest encodings are the same, find last valid
    // char in source and use memcpy.

    NextCodePointFunc nextCodePoint = getNextCodePointFunc(srcEncoding);
    EncodeFunc encode = getEncodeFunc(dstEncoding);

    const char* srcIt = srcBuffer;
    const char* prevSrcIt = srcIt;
    const char* srcEnd = srcBuffer + srcSize;
    char* dstIt = dstBuffer;
    char* dstEnd = dstBuffer + dstSize;
    uint32_t codePoint;
    while (dstIt < dstEnd &&
           nextCodePoint(codePoint, srcIt, srcEnd) == DecodeResult::Ok)
    {
        if (!encode(dstIt, dstEnd, codePoint))
            return std::make_pair((size_t)(prevSrcIt - srcBuffer),
                                  (size_t)(dstIt - dstBuffer));
        prevSrcIt = srcIt;
    }
    return std::make_pair((size_t)(srcIt - srcBuffer),
                          (size_t)(dstIt - dstBuffer));
}

std::string utf16ToUtf8(const std::wstring& s)
{
    std::string result;
    result.reserve(s.size());
    // std::copy(Utf16::beginUtf16(s), Utf16::endUtf16(s),
    //           Utf8::backInserterUtf8(result));
    return result;
}

StringConverter::StringConverter()
    : m_NextCodePoint(nullptr),
      m_Encode(nullptr),
      m_SourceEncoding(Encoding::Unknown),
      m_DestinationEncoding(Encoding::Unknown),
      m_ErrorMethod(ThrowException),
      m_InvalidCharacterSubstitute('?')
{}

StringConverter::StringConverter(NextCodePointFunc nextCodePoint,
                                 EncodeFunc encode,
                                 Encoding_t srcEncoding,
                                 Encoding_t dstEncoding)
    : m_NextCodePoint(nextCodePoint),
      m_Encode(encode),
      m_SourceEncoding(srcEncoding),
      m_DestinationEncoding(dstEncoding),
      m_ErrorMethod(ThrowException),
      m_InvalidCharacterSubstitute('?')
{}

StringConverter StringConverter::create(Encoding_t srcEncoding,
                                        Encoding_t dstEncoding)
{
    return StringConverter(getNextCodePointFunc(srcEncoding),
                           getEncodeFunc(dstEncoding),
                           srcEncoding, dstEncoding);
}

void StringConverter::setEncodings(Encoding_t srcEncoding,
                                   Encoding_t dstEncoding)
{
    m_NextCodePoint = getNextCodePointFunc(srcEncoding);
    m_Encode = getEncodeFunc(dstEncoding);
    m_SourceEncoding = srcEncoding;
    m_DestinationEncoding = dstEncoding;
}

std::pair<size_t, size_t> StringConverter::convert(const char* srcBuffer,
                                                   size_t srcSize,
                                                   char* dstBuffer,
                                                   size_t dstSize)
{
    const char* srcIt = srcBuffer;
    const char* prevSrcIt = srcIt;
    const char* srcEnd = srcBuffer + srcSize;
    char* dstIt = dstBuffer;
    char* dstEnd = dstBuffer + dstSize;
    uint32_t codePoint;
    while (dstIt < dstEnd)
    {
        int dr = m_NextCodePoint(codePoint, srcIt, srcEnd);
        if (dr != DecodeResult::Ok)
        {
            if (dr & DecodeResult::EndOfString)
            {
                break;
            }
            else if (m_ErrorMethod == ThrowException)
            {
                throw std::runtime_error("Encoding error in input");
            }
            else if (m_ErrorMethod == InsertCharacter)
            {
                if (!m_Encode(dstIt, dstEnd, m_InvalidCharacterSubstitute))
                    return std::make_pair((size_t)(prevSrcIt - srcBuffer),
                                          (size_t)(dstIt - dstBuffer));
            }
        }
        else if (!m_Encode(dstIt, dstEnd, codePoint))
        {
            return std::make_pair((size_t)(prevSrcIt - srcBuffer),
                                  (size_t)(dstIt - dstBuffer));
        }
        prevSrcIt = srcIt;
    }
    return std::make_pair((size_t)(srcIt - srcBuffer),
                          (size_t)(dstIt - dstBuffer));
}

StringConverter::ErrorMethod StringConverter::errorMethod() const
{
    return m_ErrorMethod;
}

void StringConverter::setErrorMethod(ErrorMethod errorMethod)
{
    m_ErrorMethod = errorMethod;
}

uint32_t StringConverter::invalidCharacterSubstitute() const
{
    return m_InvalidCharacterSubstitute;
}

void  StringConverter::setInvalidCharacterSubstitute(uint32_t chr)
{
    m_InvalidCharacterSubstitute = chr;
}

Encoding_t StringConverter::destinationEncoding() const
{
    return m_DestinationEncoding;
}

Encoding_t StringConverter::sourceEncoding() const
{
    return m_SourceEncoding;
}

}}
