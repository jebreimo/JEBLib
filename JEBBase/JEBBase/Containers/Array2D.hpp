/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_ARRAY2D_HPP
#define JEBBASE_CONTAINERS_ARRAY2D_HPP

#include <ostream>
#include <vector>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T>
class Array2D
{
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    Array2D();
    Array2D(size_t dim0, size_t dim1);
    Array2D(std::pair<size_t, size_t> size);
    Array2D(const Array2D<T>& other);
    Array2D(Array2D<T>&& rhs);
    ~Array2D();

    Array2D& operator=(const Array2D& rhs);
    Array2D<T>& operator=(Array2D<T>&& rhs);

    T* operator[](size_t dim0);
    const T* operator[](size_t dim0) const;

    size_t rows() const;
    size_t columns() const;

    size_t count() const;
    std::pair<size_t, size_t> size() const;
    void setSize(size_t dim0, size_t dim1);
    void setSize(std::pair<size_t, size_t> size);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    void swap(Array2D& other);
private:
    void init(std::pair<size_t, size_t> size);
    void initColumn();

    std::vector<T> m_Buffer;
    std::vector<T*> m_Column;
    std::pair<size_t, size_t> m_Size;
};

template <typename T>
bool operator==(const Array2D<T>& a, const Array2D<T>& b);
template <typename T>
bool operator!=(const Array2D<T>& a, const Array2D<T>& b);

template <typename T>
void print(std::ostream& os, const Array2D<T>& a);

template <typename T>
typename Array2D<T>::iterator begin(Array2D<T>& a)
{
    return a.begin();
}

template <typename T>
typename Array2D<T>::iterator end(Array2D<T>& a)
{
    return a.end();
}

template <typename T>
typename Array2D<T>::const_iterator begin(const Array2D<T>& a)
{
    return a.begin();
}

template <typename T>
typename Array2D<T>::const_iterator end(const Array2D<T>& a)
{
    return a.end();
}

}}

#include "Array2D_Impl.hpp"

#endif // JEB_ARRAY2D_HPP
