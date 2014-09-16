#ifndef JEBSTRING_UNICODE_CASECONVERTER_HPP
#define JEBSTRING_UNICODE_CASECONVERTER_HPP

#include <functional>
#include "CharMap.hpp"

namespace JEBString { namespace Unicode {

uint32_t lower(uint32_t ch);
uint32_t title(uint32_t ch);
uint32_t upper(uint32_t ch);

}}

#endif
