/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_BITS_BITITERATOR_HPP
#define JEB_BITS_BITITERATOR_HPP

#include <stddef.h>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Bits {

template <typename T>
class BitIterator
{
public:
    BitIterator(T bits)
        : m_Bits(bits),
          m_Index(0)
    {
    }

    bool hasNext() const
    {
        return m_Bits == 0;
    }

    size_t next()
    {
        if (m_Bits == 0)
            return ~(size_t)0;
        while ((m_Bits & 1) == 0)
        {
            m_Index++;
            m_Bits >>= 1;
        }
        m_Bits >>= 1;
        return m_Index++;
    }
private:
    T m_Bits;
    size_t m_Index;
};

}}

#endif
