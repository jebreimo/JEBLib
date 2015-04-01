/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include <algorithm>
#include <cassert>

namespace JEBBase { namespace Containers {

template <typename T>
Buffer2D<T>::Buffer2D(T* buffer,
                      size_t dim0,
                      size_t dim1,
                      size_t trailingDataSize)
    : m_TrailingDataSize(trailingDataSize),
      m_Pointers(NULL),
      m_Buffer(buffer)
{
    init(dim0, dim1);
}

template <typename T>
Buffer2D<T>::Buffer2D(const Buffer2D<T>& other)
    : m_TrailingDataSize(other.m_TrailingDataSize),
      m_Pointers(NULL),
      m_Buffer(other.m_Buffer)
{
    init(other.size(0), other.size(1));
}

template <typename T>
Buffer2D<T>::~Buffer2D()
{
    delete[] m_Pointers;
}

template <typename T>
Buffer2D<T>& Buffer2D<T>::operator=(const Buffer2D& rhs)
{
    Buffer2D<T> other(rhs);
    std::swap(m_Size[0], other.m_Size[0]);
    std::swap(m_Size[1], other.m_Size[1]);
    std::swap(m_TrailingDataSize, other.m_TrailingDataSize);
    std::swap(m_Pointers, other.m_Pointers);
    std::swap(m_Buffer, other.m_Buffer);
    return *this;
}

template <typename T>
size_t Buffer2D<T>::size(size_t dim) const
{
    assert(dim < sizeof(m_Size) / sizeof(*m_Size));
    return m_Size[dim];
}

template <typename T>
size_t Buffer2D<T>::trailingDataSize() const
{
    return m_TrailingDataSize;
}

template <typename T>
T* Buffer2D<T>::operator[](size_t dim0)
{
    assert(dim0 < m_Size[0]);
    return m_Pointers[dim0];
}

template <typename T>
const T* Buffer2D<T>::operator[](size_t dim0) const
{
    assert(dim0 < m_Size[0]);
    return m_Pointers[dim0];
}

template <typename T>
T* Buffer2D<T>::begin()
{
    return &m_Buffer[0];
}

template <typename T>
const T* Buffer2D<T>::begin() const
{
    return &m_Buffer[0];
}

template <typename T>
T* Buffer2D<T>::end()
{
    return &m_Buffer[m_Size[0] * m_Size[1]];
}

template <typename T>
const T* Buffer2D<T>::end() const
{
    return &m_Buffer[m_Size[0] * m_Size[1]];
}

template <typename T>
void Buffer2D<T>::init(size_t dim0, size_t dim1)
{
    m_Pointers = new T*[dim0];
    m_Size[0] = dim0;
    m_Size[1] = dim1;
    char* ptr = m_Buffer;
    size_t ptrIncrement = dim1 * sizeof(T) + m_TrailingDataSize;
    for (size_t i = 0; i < dim0; ++i)
    {
        m_Pointers[i] = (T*)ptr;
        ptr += ptrIncrement;
    }
}

template <typename T>
void print(std::ostream& os, const Buffer2D<T>& a)
{
    assert(a.size(0) != 0 || a.size(1) != 0);

    for (size_t i = 0; i < a.size(0); ++i)
    {
        os << a[i][0];
        for (size_t j = 1; j < a.size(1); ++j)
            os << " " << a[i][j];
        os << "\n";
    }
}

}}
