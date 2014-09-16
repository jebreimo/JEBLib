#include "Base64.hpp"

#include <algorithm>
#include <cassert>

namespace JEB {

Base64::Base64()
    : m_UpdateDecodeTable(true)
{
    char* it = m_EncodeTable;
    for (char c = 'A'; c <= 'Z'; c++)
        *it++ = c;
    for (char c = 'a'; c <= 'z'; c++)
        *it++ = c;
    for (char c = '0'; c <= '9'; c++)
        *it++ = c;
    *it++ = '+';
    *it++ = '/';
}

char Base64::operator[](size_t index) const
{
    assert(index < 64);
    return m_EncodeTable[index];
}

char& Base64::operator[](size_t index)
{
    assert(index < 64);
    m_UpdateDecodeTable = true;
    return m_EncodeTable[index];
}

size_t Base64::indexOfChar(char c) const
{
    if (m_UpdateDecodeTable)
        updateDecodeTable();
    return m_DecodeTable[(unsigned char)c];
}

size_t Base64::encodedSize(size_t decodedSize)
{
    return 4 * ((decodedSize + 2) / 3);
}

size_t Base64::decodedSize(size_t encodedSize)
{
    return 3 * ((encodedSize + 3) / 4);
}

void Base64::updateDecodeTable() const
{
    std::fill(std::begin(m_DecodeTable), std::end(m_DecodeTable), 0xFF);
    for (uint8_t i = 0; i < 64; i++)
        m_DecodeTable[static_cast<uint8_t>(m_EncodeTable[i])] = i;
    m_UpdateDecodeTable = false;
}

}
