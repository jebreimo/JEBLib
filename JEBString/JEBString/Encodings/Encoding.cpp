#include "Encoding.hpp"

#include <cassert>
#include <cstring>
#include <functional>
#include "JEBString/EncodedStrings/DecodeUtf8.hpp"
#include "JEBString/Utf8/Utf8String.hpp"

namespace JEBString { namespace Encodings {

typedef std::pair<std::string, Encoding_t> EncodingName;

static EncodingName s_EncodingMap[] = {
    EncodingName("ascii", Encoding::Ascii),
    EncodingName("us-ascii", Encoding::Ascii),
    EncodingName("utf8", Encoding::Utf8),
    EncodingName("utf-8", Encoding::Utf8),
    EncodingName("latin1", Encoding::Latin1),
    EncodingName("latin-1", Encoding::Latin1),
    EncodingName("iso8859-1", Encoding::Latin1),
    EncodingName("iso-8859-1", Encoding::Latin1),
    EncodingName("windows1252", Encoding::Windows1252),
    EncodingName("windows-1252", Encoding::Windows1252),
    EncodingName("cp1252", Encoding::Windows1252),
    EncodingName("cp-1252", Encoding::Windows1252),
    EncodingName("utf16", Encoding::Utf16),
    EncodingName("utf-16", Encoding::Utf16),
    EncodingName("utf16le", Encoding::Utf16LE),
    EncodingName("utf-16le", Encoding::Utf16LE),
    EncodingName("utf16be", Encoding::Utf16BE),
    EncodingName("utf-16be", Encoding::Utf16BE),
    EncodingName("utf32", Encoding::Utf32),
    EncodingName("utf-32", Encoding::Utf32),
    EncodingName("utf32le", Encoding::Utf32LE),
    EncodingName("utf-32le", Encoding::Utf32LE),
    EncodingName("utf32be", Encoding::Utf32BE),
    EncodingName("utf-32be", Encoding::Utf32BE),
    EncodingName("ucs-2", Encoding::Ucs2)
};

static EncodingProperties s_Properties[] = {
    EncodingProperties(Encoding::Unknown, "Unknown", "",
                       JEBBase::Bits::UnknownEndianness, 0, 0, 0),
    EncodingProperties(Encoding::Ascii, "ASCII", "",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 1),
    EncodingProperties(Encoding::Utf8, "UTF-8", "\xEF\xBB\xBF",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 4),
    EncodingProperties(Encoding::Latin1, "latin-1", "",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 1),
    EncodingProperties(Encoding::Windows1252, "windows-1252", "",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 1),
    EncodingProperties(Encoding::Utf16BE, "UTF-16BE", "\xFE\xFF",
                       JEBBase::Bits::BigEndian, 2, 1, 2),
    EncodingProperties(Encoding::Utf16LE, "UTF-16LE", "\xFF\xFE",
                       JEBBase::Bits::LittleEndian, 2, 1, 2),
    EncodingProperties(Encoding::Utf32BE, "UTF-32BE", "\x00\x00\xFE\xFF",
                       JEBBase::Bits::BigEndian, 4, 1, 1),
    EncodingProperties(Encoding::Utf32BE, "UTF-32LE", "\xFF\xFE\x00\x00",
                       JEBBase::Bits::LittleEndian, 4, 1, 1),
    EncodingProperties(Encoding::Utf7, "UTF-7", "\x2B\x2F\x76",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 0),
    EncodingProperties(Encoding::Utf1, "UTF-1", "\xF7\x64\x4C",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 5),
    EncodingProperties(Encoding::UtfEbcdic, "UTF-EBCDIC", "\xDD\x73\x66\x73",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 5),
    EncodingProperties(Encoding::Scsu, "SCSU", "\x0E\xFE\xFF",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 0),
    EncodingProperties(Encoding::Bocu1, "BOCU-1", "\xFB\xEE\x28",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 0),
    EncodingProperties(Encoding::Ucs2, "UCS2", "",
                       JEBBase::Bits::BigEndian, 2, 1, 1),
    EncodingProperties(Encoding::Gb18030, "GB18030", "\x84\x31\x95\x33",
                       JEBBase::Bits::UnknownEndianness, 1, 1, 4)
};

const EncodingProperties* encodingProperties(Encoding_t encoding)
{
    if (Encoding::Unknown <= encoding && encoding < Encoding::Maximum)
        return &s_Properties[encoding];
    else
        return NULL;
}

Encoding_t encodingFromName(const std::string& name)
{
    for (EncodingName* it = std::begin(s_EncodingMap); it != std::end(s_EncodingMap); ++it)
    {
        if (Utf8::caseInsensitiveEqual(it->first, name))
            return it->second;
    }
    return Encoding::Unknown;
}

Encoding_t encodingFromByteOrderMark(const std::string& str)
{
    for (size_t i = 0; i < sizeof(s_Properties) / sizeof(*s_Properties); i++)
    {
        const std::string& bom = s_Properties[i].byteOrderMark();
        if (!bom.empty() &&
            str.size() >= bom.size() &&
            std::equal(bom.begin(), bom.end(), str.begin()))
        {
            if (s_Properties[i].encoding() != Encoding::Utf7 ||
                (str.size() >= 4 && (str[3] == '8' || str[3] == '9' ||
                                     str[3] == '+' || str[3] == '/')))

                return s_Properties[i].encoding();
        }
    }
    return Encoding::Unknown;
}

Encoding_t encodingFromByteOrderMark(const char* str, size_t len)
{
    assert(str != NULL);
    assert(len > 0);
    return encodingFromByteOrderMark(std::string(str, std::min(len, (size_t)4)));
}

bool getBytePatterns(const char* str, size_t len,
                     size_t patternSize,
                     unsigned& anded, unsigned& ored)
{
    assert(patternSize < sizeof(unsigned) * 8);
    if (len < patternSize)
        return false;
    anded = ~0u;
    ored = 0;
    for (size_t i = 0; i + patternSize <= len; i += patternSize)
    {
        unsigned pattern = 0;
        for (size_t j = 0; j < patternSize; j++)
            pattern |= str[i + j] == 0 ? 0 : (unsigned)(1u << j);

        anded &= pattern;
        ored |= pattern;
    }
    return true;
}

Encoding_t encodingFromPattern(unsigned pattern, size_t patternSize)
{
    if (patternSize == 4)
    {
        switch (pattern)
        {
        case 0x1: return Encoding::Utf32LE;
        case 0x3: return Encoding::Utf32LE;
        case 0x5: return Encoding::Utf16LE;
        case 0x8: return Encoding::Utf32BE;
        case 0xA: return Encoding::Utf16BE;
        case 0xC: return Encoding::Utf32BE;
        case 0xF: return Encoding::Utf8;
        default: return Encoding::Unknown;
        }
    }
    else if (patternSize == 2)
    {
        switch (pattern)
        {
        case 0x1: return Encoding::Utf16LE;
        case 0x2: return Encoding::Utf16BE;
        case 0x3: return Encoding::Utf8;
        default: return Encoding::Unknown;
        }
    }
    else if (patternSize == 1)
    {
        return Encoding::Utf8;
    }
    else
    {
        return Encoding::Unknown;
    }
}

Encoding_t encodingFromString(const char* str, size_t len,
                                  bool ignoreLastCharacter)
{
    size_t patternSize;
    if (len % 4 == 0)
        patternSize = 4;
    else if (len % 2 == 0)
        patternSize = 2;
    else
        patternSize = 1;
    unsigned anded, ored;
    if (!getBytePatterns(str, len, patternSize, anded, ored))
        return Encoding::Unknown;

    Encoding_t enc1 = encodingFromPattern(anded, patternSize);
    Encoding_t enc2 = encodingFromPattern(ored, patternSize);
    if (enc1 != enc2)
        return Encoding::Unknown;
    else if (enc1 != Encoding::Utf8)
        return enc1;
    else if (EncodedStrings::isValidUtf8(str, str + len, ignoreLastCharacter))
        return Encoding::Utf8;
    else
        return Encoding::Windows1252;
}

Encoding_t encodingFromString(const std::string& str)
{
    return encodingFromString(str.c_str(), str.size(), false);
}

std::pair<Encoding_t, const char*> readEncoding(
        const char* buffer, size_t length)
{
    if (length == 0)
        return std::make_pair(Encoding::Unknown, buffer);
    Encoding_t encoding = encodingFromByteOrderMark(buffer, length);
    if (encoding == Encoding::Unknown)
    {
        return std::make_pair(encodingFromString(buffer, length, true),
                              buffer);
    }
    else
    {
        const std::string& bom = encodingProperties(encoding)->byteOrderMark();
        return std::make_pair(encoding, buffer + bom.size());
    }
}

Encoding_t readEncoding(std::istream& stream, size_t maxScanLength)
{
    std::streampos pos = stream.tellg();
    std::vector<char> buffer(maxScanLength);
    stream.read(&buffer[0], buffer.size());
    auto result = readEncoding(&buffer[0], maxScanLength);
    stream.seekg(pos + std::streampos(result.second - &buffer[0]));
    return result.first;
}

}}
