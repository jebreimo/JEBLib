/* JEBBase: generic algorithms and functions
 * Copyright 2015 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_CIRCULARARRAY2D_HPP
#define JEBBASE_CONTAINERS_CIRCULARARRAY2D_HPP

#include "Array2D.hpp"

namespace JEBBase { namespace Containers {

template <typename T>
class CircularArrayWrapper
{
public:
    CircularArrayWrapper(T* data, size_t size);

    T& operator[](size_t size);
private:
    T* m_Data;
    size_t m_Size;
};

template <typename T>
class CircularArray2D
{
public:
    CircularArray2D();
    CircularArray2D(size_t dim0, size_t dim1);
    CircularArray2D(const Array2D<T>& data);
    CircularArray2D(Array2D<T>&& data);
    CircularArray2D(std::pair<size_t, size_t> size);

    CircularArrayWrapper<T> operator[](size_t i);
    CircularArrayWrapper<const T> operator[](size_t i) const;

    size_t rows() const;
    size_t columns() const;

    size_t count() const;
    std::pair<size_t, size_t> size() const;
    void setSize(size_t dim0, size_t dim1);
    void setSize(std::pair<size_t, size_t> size);

    Array2D<T>& data();
    const Array2D<T>& data() const;
private:
    Array2D<T> m_Data;
};

}}

#include "CircularArray2D-Impl.hpp"

#endif
