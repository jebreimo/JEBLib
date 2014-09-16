#ifndef JEBSTRING_ENCODINGS_STRINGCONVERTER_HPP
#define JEBSTRING_ENCODINGS_STRINGCONVERTER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "JEBString/JEBStringDefinitions.hpp"
#include "JEBString/JEBStringFlags.hpp"

namespace JEBString { namespace Encodings {

// template <typename InpIt, typename OutIt>
// bool convert(InpIt begin, InpIt end,
//              Encoding_t inEncoding,
//              OutIt outBeg, OutIt outEnd,
//              Encoding_t outEncoding)
// {

// }

class StringConverter
{
public:
    enum ErrorMethod {ThrowException, Ignore, InsertCharacter};
    static StringConverter create(Encoding_t srcEncoding,
                                  Encoding_t dstEncoding);

    StringConverter();

    void setEncodings(Encoding_t srcEncoding, Encoding_t dstEncoding);
    std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                      char* dstBuffer, size_t dstSize);
    ErrorMethod errorMethod() const;
    void setErrorMethod(ErrorMethod errorMethod);

    uint32_t invalidCharacterSubstitute() const;
    void setInvalidCharacterSubstitute(uint32_t chr);

    Encoding_t destinationEncoding() const;
    Encoding_t sourceEncoding() const;
private:
    typedef unsigned (*NextCodePointFunc)(uint32_t&, const char*&,
                                          const char*);
    typedef bool (*EncodeFunc)(char*&, char*, uint32_t);

    StringConverter(NextCodePointFunc nextCodePoint, EncodeFunc encode,
                    Encoding_t srcEncoding, Encoding_t dstEncoding);

    NextCodePointFunc m_NextCodePoint;
    EncodeFunc m_Encode;
    Encoding_t m_SourceEncoding;
    Encoding_t m_DestinationEncoding;
    ErrorMethod m_ErrorMethod;
    uint32_t m_InvalidCharacterSubstitute;
};

std::pair<size_t, size_t> convert(const char* srcBuffer, size_t srcSize,
                                  Encoding_t srcEncoding,
                                  char* dstBuffer, size_t dstSize,
                                  Encoding_t dstEncoding);

std::string utf16ToUtf8(const std::wstring& s);
// std::string utf16LEToUtf8(const std::wstring& s);
// std::string utf16BEToUtf8(const std::wstring& s);

// std::wstring utf8ToUtf16(const std::string& s);
// std::wstring utf8ToUtf16LE(const std::string& s);
// std::wstring utf8ToUtf16BE(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32LE(const std::string& s);
// std::vector<uint32_t> utf8ToUtf32BE(const std::string& s);

}}

#endif
