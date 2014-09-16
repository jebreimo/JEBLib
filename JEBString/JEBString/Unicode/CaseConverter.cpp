#include "CaseConverter.hpp"
#include "StandardLowerCase.hpp"
#include "StandardTitleCase.hpp"
#include "StandardUpperCase.hpp"

namespace JEBString { namespace Unicode {

namespace
{
    CharMap lowerMap(CompactLowerCaseMappings, LowerCaseMappings);
    CharMap titleMap(CompactTitleCaseMappings, TitleCaseMappings);
    CharMap upperMap(CompactUpperCaseMappings, UpperCaseMappings);
}

uint32_t lower(uint32_t ch)
{
    return lowerMap.get(ch);
}

uint32_t title(uint32_t ch)
{
    return titleMap.get(ch);
}

uint32_t upper(uint32_t ch)
{
    return upperMap.get(ch);
}

}}
