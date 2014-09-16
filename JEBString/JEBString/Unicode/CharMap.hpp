#ifndef JEBSTRING_UNICODE_CHARMAP_HPP
#define JEBSTRING_UNICODE_CHARMAP_HPP

#include <map>
#include <vector>
#include "CharMappingTypes.hpp"

namespace JEBString { namespace Unicode {

class CharMap
{
public:
    template <size_t M, size_t N>
    CharMap(const CompactCharMapping (&compactMappings)[M],
            const CharMapping (&mappings)[N]);
    CharMap(const CompactCharMapping* compactMappings,
            size_t compactMappingsSize,
            const CharMapping* mappings,
            size_t mappingsSize);

    uint32_t get(uint32_t chr) const;
    bool has(uint32_t chr) const;
private:
    bool findInCompactMapping(uint32_t chr, uint32_t& mappedChr) const;
    bool findInMapping(uint32_t chr, uint32_t& mappedChr) const;

    const CompactCharMapping* m_CompactMappings;
    const CharMapping* m_Mappings;
    size_t m_CompactMappingsSize;
    size_t m_MappingsSize;
};

template <size_t M, size_t N>
CharMap::CharMap(const CompactCharMapping (&compactMappings)[M],
                 const CharMapping (&mappings)[N])
    : m_CompactMappings(compactMappings),
      m_Mappings(mappings),
      m_CompactMappingsSize(M),
      m_MappingsSize(N)
{
}

}}

#endif
