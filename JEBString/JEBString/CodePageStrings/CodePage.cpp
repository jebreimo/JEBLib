#include "CodePage.hpp"
#include <vector>
#include <stdexcept>
#include "JEBBase/Algorithms/KeyFunctionAlgorithms.hpp"

namespace JEBString { namespace CodePageStrings {

namespace detail
{
    const std::pair<uint32_t, uint8_t> Windows1252SpecialChars[] = {
        {0x0152, 0x8C}, {0x0153, 0x9C}, {0x0160, 0x8A}, {0x0161, 0x9A},
        {0x0178, 0x9F}, {0x017D, 0x8E}, {0x017E, 0x9E}, {0x0192, 0x83},
        {0x02DC, 0x98}, {0x2013, 0x96}, {0x2014, 0x97}, {0x2018, 0x91},
        {0x2019, 0x92}, {0x201A, 0x82}, {0x201C, 0x93}, {0x201D, 0x94},
        {0x201E, 0x84}, {0x2020, 0x86}, {0x2021, 0x87}, {0x2022, 0x95},
        {0x2026, 0x85}, {0x2030, 0x89}, {0x2039, 0x8B}, {0x203A, 0x9B},
        {0x20AC, 0x80}, {0x20C6, 0x88}, {0x2122, 0x99}
    };

    const uint32_t* windows1252ToUnicode()
    {
        static std::vector<uint32_t> table;
        if (table.empty())
        {
            table.resize(256);
            for (uint32_t i = 0; i < 256; ++i)
                table[i] = i;
            for (auto it = std::begin(Windows1252SpecialChars);
                 it != std::end(Windows1252SpecialChars); ++it)
                table[it->second] = it->first;
        }
        return &table[0];
    }

    std::pair<const std::pair<uint32_t, uint8_t>*,
              const std::pair<uint32_t, uint8_t>*> unicodeToWindows1252()
    {
        return std::make_pair(std::begin(Windows1252SpecialChars),
                              std::end(Windows1252SpecialChars));
    }

    CodePage makeWindows1252()
    {
        auto to = windows1252ToUnicode();
        auto from = unicodeToWindows1252();
        return CodePage(to, from.first, from.second, Encoding::Windows1252);
    }

    const uint32_t* latin1ToUnicode()
    {
        static std::vector<uint32_t> table;
        if (table.empty())
        {
            table.resize(256);
            for (uint32_t i = 0; i < 256; ++i)
                table[i] = i;
        }
        return &table[0];
    }

    std::pair<const std::pair<uint32_t, uint8_t>*,
              const std::pair<uint32_t, uint8_t>*> unicodeToLatin1()
    {
        return std::pair<const std::pair<uint32_t, uint8_t>*,
                         const std::pair<uint32_t, uint8_t>*>(nullptr,
                                                              nullptr);
    }

    CodePage makeLatin1()
    {
        auto to = latin1ToUnicode();
        auto from = unicodeToLatin1();
        return CodePage(to, from.first, from.second, Encoding::Latin1);
    }
}

CodePage::CodePage(const uint32_t* toCodePoints,
                   const CodePointMapping* firstFromCodePoints,
                   const CodePointMapping* lastFromCodePoints,
                   JEBString::Encoding_t encoding)
    : m_ToCodePoints(toCodePoints),
      m_FirstFromCodePoints(firstFromCodePoints),
      m_LastFromCodePoints(lastFromCodePoints),
      m_Encoding(encoding)
{}

uint32_t CodePage::toCodePoint(char c) const
{
    return m_ToCodePoints[static_cast<uint8_t>(c)];
}

uint32_t CodePage::fromCodePoint(uint32_t c) const
{
    if (c < 256 && m_ToCodePoints[c] == c)
        return c;
    auto it = JEBBase::Algorithms::binaryFind(
        m_FirstFromCodePoints, m_LastFromCodePoints, c,
        [](const std::pair<uint32_t, char>& p){return p.first;});
    if (it != m_LastFromCodePoints)
        return it->second;
    return ~(uint32_t)0;
}

JEBString::Encoding_t CodePage::encoding() const
{
    return m_Encoding;
}

CodePage codePage(Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::Latin1:
        return detail::makeLatin1();
    case Encoding::Windows1252:
        return detail::makeWindows1252();
    default:
        break;
    }
    throw std::logic_error("Unsupported code page encoding.");
}

}}
