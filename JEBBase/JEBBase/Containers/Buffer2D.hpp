/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_BUFFER2D_HPP
#define JEBBASE_CONTAINERS_BUFFER2D_HPP

#include <cstddef>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T>
class Buffer2D
{
public:
    Buffer2D(T* buffer,
             size_t dim0,
             size_t dim1,
             size_t trailingDataSize = 0);
    Buffer2D(const Buffer<T>& other);
    ~Buffer2D();

    Buffer2D& operator=(const Buffer2D& rhs);

    size_t size(size_t dim) const;

    size_t trailingDataSize() const;

    T* operator[](size_t dim0);
    const T* operator[](size_t dim0) const;

    T* begin();
    const T* begin() const;

    T* end();
    const T* end() const;
private:
    void  init(size_t dim0, size_t dim1);

    size_t m_Size[2];
    size_t m_TrailingDataSize;
    T** m_Pointers;
    T* m_Buffer;
};

}}

#include "Buffer2D_Impl.hpp"

#endif
