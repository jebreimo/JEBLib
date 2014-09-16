/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include <cstddef>
#include "JEBBase/JEBBaseDefinitions.hpp"

#ifndef JEBBASE_BITS_BITS_HPP
#define JEBBASE_BITS_BITS_HPP

/** @file
    @brief Define several functions for testing and manipulating bits.
*/

namespace JEBBase
{
/** @brief Groups together functions for querying and manipulating bits.
  */
namespace Bits
{

/** @brief Returns the bit at index @a index in @a bits.
    @note First bit has index 0.
*/
template <typename T>
bool getBit(T bits, size_t index);

template <typename T>
bool getBit(const T* bits, size_t bitsLen, size_t index);

/** @brief Sets the bit at index @a index to @a value in @a bits.
    @note First bit has index 0.
*/
template <typename T>
void setBit(T& bits, size_t index, bool value);

template <typename T>
void setBit(T* bits, size_t bitsLen, size_t index, bool value);

/** @brief Inverts the bit at index @a index in @a bits.
    @note First bit has index 0.
*/
template <typename T>
void invertBit(T& bits, size_t index);

/** @brief Returns the number of set bits (ones) in @a bits
*/
template <typename T>
size_t countOnes(T bits);

/** @brief Returns the index of the lowest order 1-bit in @a bits.
    @return the 0-based index of the lowest-order 1-bit in @a bits or
            SIZE_MAX if @a bits is 0.
*/
template <typename T>
size_t lowestOne(T bits);

template <typename T>
size_t lowestOneInRange(T bits, size_t minIndex, size_t maxIndex = sizeof(T) * 8);

/** @brief Returns the index of the highest order 1-bit in @a bits.
    @return the 0-based index of the highest-order 1-bit in @a bits or
            SIZE_MAX if @a bits is 0.
*/
template <typename T>
size_t highestOne(T bits);

/** @brief Returns the number of set bits in @a bits in the given range.
    @param bits the bit-set.
    @param minIndex the lower index (inclusive)
    @param maxIndex the upper index (non-inclusive)
*/
template <typename T>
size_t countOnesInRange(T bits, size_t minIndex, size_t maxIndex);

/** @brief Returns the index of the @a nth set bit in @a bits.
    @return the 0-based index of the @a nth set bit in @a bits or
            SIZE_MAX if @a bits has less than @a n set bits.
*/
template <typename T>
size_t nthOne(T bits, size_t n);

/** @brief Returns true if only a single bit in @a bits is 1.
 */
template <typename T>
bool isPowerOfTwo(T bits);

}
}

#include "Bits_Impl.hpp"

#endif
