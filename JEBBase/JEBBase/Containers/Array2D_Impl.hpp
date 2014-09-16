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
Array2D<T>::Array2D()
    : m_Size(0, 0)
{}

template <typename T>
Array2D<T>::Array2D(size_t dim0, size_t dim1)
    : m_Buffer(dim0 * dim1),
      m_Size(dim0, dim1)
{
    initColumn();
}

template <typename T>
Array2D<T>::Array2D(std::pair<size_t, size_t> size)
    : m_Buffer(size.first * size.second),
      m_Size(size)
{
    initColumn();
}

template <typename T>
Array2D<T>::Array2D(const Array2D<T>& rhs)
    : m_Buffer(rhs.m_Buffer),
      m_Size(rhs.m_Size)
{
    initColumn();
}

template <typename T>
Array2D<T>::Array2D(Array2D<T>&& rhs)
    : m_Buffer(std::move(rhs.m_Buffer)),
      m_Column(std::move(rhs.m_Column)),
      m_Size(rhs.m_Size)
{
    rhs.m_Size = std::make_pair(0, 0);
}

template <typename T>
Array2D<T>::~Array2D()
{
}

template <typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
    m_Buffer = rhs.m_Buffer;
    if (rhs.size() != m_Size)
    {
        m_Size = rhs.m_Size;
        initColumn();
    }
    return *this;
}

template <typename T>
Array2D<T>& Array2D<T>::operator=(Array2D&& rhs)
{
    m_Size = rhs.m_Size;
    rhs.m_Size = std::make_pair(0, 0);
    m_Buffer = std::move(rhs.m_Buffer);
    m_Column = std::move(rhs.m_Column);
    return *this;
}

template <typename T>
T* Array2D<T>::operator[](size_t dim0)
{
    assert(dim0 < m_Size.first);
    return m_Column[dim0];
}

template <typename T>
const T* Array2D<T>::operator[](size_t dim0) const
{
    assert(dim0 < m_Size.first);
    return m_Column[dim0];
}

template <typename T>
size_t Array2D<T>::rows() const
{
    return m_Size.first;
}

template <typename T>
size_t Array2D<T>::columns() const
{
    return m_Size.second;
}

template <typename T>
std::pair<size_t, size_t> Array2D<T>::size() const
{
    return m_Size;
}

template <typename T>
void Array2D<T>::setSize(size_t dim0, size_t dim1)
{
    setSize(std::make_pair(dim0, dim1));
}

template <typename T>
void Array2D<T>::setSize(std::pair<size_t, size_t> size)
{
    if (size == m_Size)
        return;

    if (size.first * size.second != m_Size.first * m_Size.second)
        m_Buffer.resize(size.first * size.second);

    m_Size = size;
    initColumn();
}

template <typename T>
auto Array2D<T>::begin() -> iterator
{
    return m_Buffer.begin();
}

template <typename T>
auto Array2D<T>::begin() const -> const_iterator
{
    return m_Buffer.begin();
}

template <typename T>
auto Array2D<T>::cbegin() const -> const_iterator
{
    return m_Buffer.begin();
}

template <typename T>
auto Array2D<T>::end() -> iterator
{
    return m_Buffer.end();
}

template <typename T>
auto Array2D<T>::end() const -> const_iterator
{
    return m_Buffer.end();
}

template <typename T>
auto Array2D<T>::cend() const -> const_iterator
{
    return m_Buffer.end();
}

template <typename T>
void Array2D<T>::swap(Array2D<T>& other)
{
    std::swap(m_Buffer, other.m_Buffer);
    std::swap(m_Column, other.m_Column);
    std::swap(m_Size, other.m_Size);
}

template <typename T>
void Array2D<T>::initColumn()
{
    m_Column.resize(m_Size.first);
    for (size_t i = 0; i < m_Size.first; ++i)
        m_Column[i] = &m_Buffer[i * m_Size.second];
}

template <typename T>
bool operator==(const Array2D<T>& a, const Array2D<T>& b)
{
    return a.size() == b.size() &&
           std::equal(a.begin(), a.end(), b.begin());
}

template <typename T>
bool operator!=(const Array2D<T>& a, const Array2D<T>& b)
{
    return !(a == b);
}

template <typename T>
void print(std::ostream& os, const Array2D<T>& a)
{
    assert(a.size().first != 0 || a.size().second != 0);

    for (size_t i = 0; i < a.size().first; ++i)
    {
        os << a[i][0];
        for (size_t j = 1; j < a.size().second; ++j)
            os << " " << a[i][j];
        os << "\n";
    }
}

}}
