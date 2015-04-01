/* JEBBase: generic algorithms and functions
 * Copyright 2015 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include <algorithm>
#include <cassert>

namespace JEBBase { namespace Containers {

template <typename T>
CircularArrayWrapper<T>::CircularArrayWrapper(T* data, size_t size)
    : m_Data(data),
      m_Size(size)
{}

template <typename T>
T& CircularArrayWrapper<T>::operator[](size_t index)
{
    return m_Data[index % m_Size];
}

template <typename T>
CircularArray2D<T>::CircularArray2D()
{}

template <typename T>
CircularArray2D<T>::CircularArray2D(size_t dim0, size_t dim1)
    : m_Data(dim0, dim1)
{}

template <typename T>
CircularArray2D<T>::CircularArray2D(std::pair<size_t, size_t> size)
    : m_Data(size)
{}

template <typename T>
CircularArray2D<T>::CircularArray2D(const Array2D<T>& data)
    : m_Data(data)
{}

template <typename T>
CircularArray2D<T>::CircularArray2D(Array2D<T>&& data)
    : m_Data(std::move(data))
{}

template <typename T>
CircularArrayWrapper<T> CircularArray2D<T>::operator[](size_t i)
{
    return CircularArrayWrapper<T>(m_Data[i % m_Data.rows()],
                                   m_Data.columns());
}

template <typename T>
CircularArrayWrapper<const T> CircularArray2D<T>::operator[](size_t i) const
{
    return CircularArrayWrapper<const T>(m_Data[i % m_Data.rows()],
                                         m_Data.columns());
}

template <typename T>
size_t CircularArray2D<T>::rows() const
{
    return m_Data.rows();
}

template <typename T>
size_t CircularArray2D<T>::columns() const
{
    return m_Data.columns();
}

template <typename T>
std::pair<size_t, size_t> CircularArray2D<T>::size() const
{
    return m_Data.size();
}

template <typename T>
void CircularArray2D<T>::setSize(size_t dim0, size_t dim1)
{
    m_Data.setSize(dim0, dim1);
}

template <typename T>
void CircularArray2D<T>::setSize(std::pair<size_t, size_t> size)
{
    m_Data.setSize(size);
}

template <typename T>
Array2D<T>& CircularArray2D<T>::data()
{
    return m_Data;
}

template <typename T>
const Array2D<T>& CircularArray2D<T>::data() const
{
    return m_Data;
}

}}
