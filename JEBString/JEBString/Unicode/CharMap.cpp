#include "CharMap.hpp"

#include <cassert>
#include "JEBBase/JEBAlgorithms.hpp"

namespace JEBString { namespace Unicode {

using namespace JEBBase;

uint32_t segment(const CompactCharMapping& ccs)
{
    return ccs.segment;
}

uint32_t key(const CharMapping& mapping)
{
    return mapping.chr;
}

static const uint32_t SegMask = ~(uint32_t)0x1F;

CharMap::CharMap(const CompactCharMapping* compactMappings,
                 size_t compactMappingsSize,
                 const CharMapping* mappings,
                 size_t mappingsSize)
    : m_CompactMappings(compactMappings),
      m_Mappings(mappings),
      m_CompactMappingsSize(compactMappingsSize),
      m_MappingsSize(mappingsSize)
{
    assert(compactMappings);
    assert(mappings || mappingsSize == 0);
    assert(compactMappingsSize != 0);
    assert(compactMappings[0].segment < 0x80);
    assert(compactMappingsSize == 1 || compactMappings[1].segment >= 0x80);
}

uint32_t CharMap::get(uint32_t chr) const
{
    if (chr >= m_CompactMappings[0].segment + 1 &&
        chr <= m_CompactMappings[0].segment + 26)
        return chr + m_CompactMappings[0].offset;
    else if (chr < 128)
        return chr;

    uint32_t mappedChr = chr;
    if (findInCompactMapping(chr, mappedChr) || findInMapping(chr, mappedChr))
        return mappedChr;

    return chr;
}

bool CharMap::has(uint32_t chr) const
{
    uint32_t mappedChr = chr;
    return findInCompactMapping(chr, mappedChr) ||
           findInMapping(chr, mappedChr);
}

bool CharMap::findInCompactMapping(uint32_t chr, uint32_t& mappedChr) const
{
    const CompactCharMapping* set = Algorithms::lowerBound(
                m_CompactMappings,
                m_CompactMappings + m_CompactMappingsSize,
                chr & SegMask,
                segment);
    if (set == m_CompactMappings + m_CompactMappingsSize ||
        set->segment != (chr & SegMask))
        return false;

    return set->get(chr, mappedChr);
}

bool CharMap::findInMapping(uint32_t chr, uint32_t& mappedChr) const
{
    const CharMapping* mapping = Algorithms::lowerBound(
                m_Mappings,
                m_Mappings + m_MappingsSize,
                chr,
                key);
    if (mapping == m_Mappings + m_MappingsSize || mapping->chr != chr)
        return false;

    mappedChr = mapping->mappedChr;
    return true;
}

}}
