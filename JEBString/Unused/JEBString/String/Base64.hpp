#ifndef JEB_BASE64_HPP
#define JEB_BASE64_HPP

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include "JEB/JEBDefinitions.hpp"

namespace JEB
{

class Base64
{
public:
    Base64();

    char operator[](size_t index) const;
    char& operator[](size_t index);

    size_t indexOfChar(char c) const;

    template <typename FwdIt, typename OutIt>
    OutIt encode(FwdIt beg, FwdIt end, OutIt out) const;

    template <typename FwdIt, typename OutIt>
    OutIt decode(FwdIt beg, FwdIt end, OutIt out) const;

    static size_t encodedSize(size_t decodedSize);
    static size_t decodedSize(size_t encodedSize);
private:
    void updateDecodeTable() const;

    char m_EncodeTable[64];
    mutable uint8_t m_DecodeTable[256];
    mutable bool m_UpdateDecodeTable;
};

template <typename FwdIt, typename OutIt>
OutIt Base64::encode(FwdIt beg, FwdIt end, OutIt out) const
{
    while (beg != end)
    {
        uint32_t tmp = 0;
        for (size_t i = 0; i < 3; i++)
        {
            if (beg == end)
            {
                tmp <<= (3 - i) * 8;
                break;
            }
            tmp <<= 8;
            tmp |= static_cast<uint8_t>(*beg++);
        }
        *out++ = m_EncodeTable[tmp >> 18];
        *out++ = m_EncodeTable[(tmp >> 12) & 0x3F];
        *out++ = m_EncodeTable[(tmp >> 6) & 0x3F];
        *out++ = m_EncodeTable[tmp & 0x3F];
    }
    return out;
}

template <typename FwdIt, typename OutIt>
OutIt Base64::decode(FwdIt beg, FwdIt end, OutIt out) const
{
    if (m_UpdateDecodeTable)
        updateDecodeTable();
    while (beg != end)
    {
        uint32_t tmp = 0;
        for (size_t i = 0; i < 4; i++)
        {
            if (beg == end)
            {
                tmp <<= (4 - i) * 6;
                break;
            }
            uint8_t index = static_cast<uint8_t>(*beg++);
            if (m_DecodeTable[index] == 0xFF)
                throw std::runtime_error("Received character is not among the base64 digits.");
            tmp <<= 6;
            tmp |= m_DecodeTable[index];
        }
        *out++ = (uint8_t)(tmp >> 16);
        *out++ = (uint8_t)((tmp >> 8) & 0xFF);
        *out++ = (uint8_t)(tmp & 0xFF);
    }
    return out;
}

}

#endif
