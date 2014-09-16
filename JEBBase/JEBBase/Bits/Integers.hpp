/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_INTEGERS_HPP
#define JEBBASE_BITS_INTEGERS_HPP

#include <cstdint>

namespace JEBBase { namespace Bits {

template <size_t Size>
struct EquvalentUnsignedIntType
{};

template <>
struct EquvalentUnsignedIntType<1>
{
    typedef uint8_t Type;
};

template <>
struct EquvalentUnsignedIntType<2>
{
    typedef uint16_t Type;
};

template <>
struct EquvalentUnsignedIntType<4>
{
    typedef uint32_t Type;
};

template <>
struct EquvalentUnsignedIntType<8>
{
    typedef uint64_t Type;
};

}}

#endif
