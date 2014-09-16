/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "BitSet.hpp"

#include <limits>
#include "Bits.hpp"

namespace JEBBase { namespace Bits {

const size_t BitSet::NotFound = std::numeric_limits<size_t>::max();
const size_t BitSet::BitsPerWord = sizeof(BitSet::Word) * 8;

BitSet::BitSet()
    : m_Size(0)
{
}

BitSet::BitSet(size_t size)
    : m_Bits(containerSize(size)),
      m_Size(size)
{
}

size_t BitSet::size() const
{
    return m_Size;
}

void BitSet::setSize(size_t size)
{
    m_Bits.resize(containerSize(size));
    m_Size = size;
}

bool BitSet::bit(size_t index)
{
    size_t index1 = index / BitsPerWord;
    size_t index2 = index % BitsPerWord;
    return Bits::getBit(m_Bits[index1], index2);
}

void BitSet::setBit(size_t index, bool bit)
{
    size_t index1 = index / BitsPerWord;
    size_t index2 = index % BitsPerWord;
    return Bits::setBit(m_Bits[index1], index2, bit);
}

size_t BitSet::findFirst(bool value, size_t fromIndex)
{
    if (fromIndex >= m_Size)
        return NotFound;

    size_t majIndex = fromIndex / BitsPerWord;
    size_t minIndex = fromIndex % BitsPerWord;
    size_t count = majIndex * BitsPerWord;

    if (count + BitsPerWord > m_Size)
        return first(value, majIndex, minIndex, m_Size % BitsPerWord);

    if (minIndex != 0)
    {
        size_t index = first(value, majIndex, minIndex, BitsPerWord);
        if (index != NotFound)
            return index;
        majIndex++;
        count += BitsPerWord;
    }
    while (count + BitsPerWord <= m_Size)
    {
        size_t index = first(value, majIndex);
        if (index != NotFound)
            return index;
        majIndex++;
        count += BitsPerWord;
    }
    if (count < m_Size)
        return first(value, majIndex, 0, m_Size % BitsPerWord);
    return NotFound;
}

size_t BitSet::containerSize(size_t size)
{
    return (size + BitsPerWord - 1) / BitsPerWord;
}

size_t BitSet::first(bool value, size_t major)
{
    Word word = value ? m_Bits[major] : ~m_Bits[major];
    size_t index = Bits::lowestOne(word);
    if (index != NotFound)
        return major * BitsPerWord + index;
    else
        return NotFound;
}

size_t BitSet::first(bool value, size_t major, size_t minorMin, size_t minorMax)
{
    Word word = value ? m_Bits[major] : ~m_Bits[major];
    size_t index = Bits::lowestOneInRange(word, minorMin, minorMax);
    if (index != NotFound)
        return major * BitsPerWord + index;
    else
        return NotFound;
}

}}
