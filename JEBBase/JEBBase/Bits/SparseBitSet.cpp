/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "SparseBitSet.hpp"

#include <algorithm>
#include "Bits.hpp"

namespace JEBBase { namespace Bits {

SparseBitSet::SparseBitSet(size_t size, size_t bucketSize)
    : m_Size(size),
      m_BucketSize(bucketSize),
      m_Buckets((size + bucketSize - 1) / bucketSize)
{
}

SparseBitSet::~SparseBitSet()
{
    clear();
}

size_t SparseBitSet::size() const
{
    return m_Size;
}

void SparseBitSet::setSize(size_t size)
{
    m_Size = size;
    clear();
    m_Buckets.resize((size + m_BucketSize - 1) / m_BucketSize);
}

size_t SparseBitSet::bucketSize() const
{
    return m_BucketSize;
}

void SparseBitSet::setBucketSize(size_t bucketSize)
{
    m_BucketSize = bucketSize;
    clear();
    m_Buckets.resize((m_Size + bucketSize - 1) / bucketSize);
}

bool SparseBitSet::bit(size_t index) const
{
    auto bucket = m_Buckets[index / m_BucketSize];
    if (!bucket)
        return false;
    size_t bucketPos = index % m_BucketSize;
    return Bits::getBit(bucket[bucketPos / (8 * sizeof(unsigned))],
                        bucketPos % (8 * sizeof(unsigned)));
}

void SparseBitSet::setBit(size_t index, bool value)
{
    auto bucket = m_Buckets[index / m_BucketSize];
    if (bucket == NULL && !value)
        return;

    if (!bucket)
        bucket = createBucket(index / m_BucketSize);

    size_t bucketPos = index % m_BucketSize;
    return Bits::setBit(bucket[bucketPos / (8 * sizeof(unsigned))],
                        bucketPos % (8 * sizeof(unsigned)),
                        value);
}

size_t SparseBitSet::bucketCount() const
{
    return m_Buckets.size();
}

size_t SparseBitSet::usedBucketCount() const
{
    size_t count = 0;
    for (auto it = m_Buckets.begin(); it != m_Buckets.end(); it++)
    {
        if (*it)
            count++;
    }
    return count;
}

void SparseBitSet::clear()
{
    for (auto it = m_Buckets.begin(); it != m_Buckets.end(); it++)
    {
        if (*it)
        {
            delete[] *it;
            *it = NULL;
        }
    }
}

unsigned* SparseBitSet::createBucket(size_t index)
{
    auto bucket = new unsigned[m_BucketSize / (8 * sizeof(unsigned))];
    m_Buckets[index] = bucket;
    std::fill(&bucket[0], &bucket[m_BucketSize / (8 * sizeof(unsigned))], 0);
    return bucket;
}

}}
