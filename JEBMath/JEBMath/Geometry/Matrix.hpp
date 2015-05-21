#ifndef JEBMATH_GEOMETRY_MATRIX_HPP
#define JEBMATH_GEOMETRY_MATRIX_HPP

#include <array>
#include <initializer_list>
#include <stdexcept>

namespace JEBMath {

template <typename T, unsigned N>
class Matrix
{
public:
    static unsigned rows() {return N;}
    static unsigned cols() {return N;}
    static unsigned size() {return N * N;}

    Matrix()
    {
        m_Values.fill(0);
    }

    Matrix(std::initializer_list<T> v)
    {
        if (v.size() != size())
            throw std::invalid_argument("Incorrect number of arguments.");
        auto it = v.begin();
        for (auto dst = begin(); dst != end(); ++dst, ++it)
            *dst = *it;
    }

    template <typename U>
    Matrix(U (&arr)[N * N])
    {
        for (auto dst = begin(); dst != end(); ++dst, ++arr)
            *dst = T(*arr);
    }

    template <typename U>
    explicit Matrix(const Matrix<U, N>& other)
    {
        auto src = other.begin();
        for (auto dst = begin(); dst != end(); ++dst, ++src)
            *dst = T(*src);
    }

    template <typename U>
    Matrix<T, N>& operator=(const Matrix<U, N>& other)
    {
        auto src = other.begin();
        for (auto dst = begin(); dst != end(); ++dst, ++src)
            *dst = T(*src);
        return *this;
    }

    T* operator[](unsigned row)
    {
        return &m_Values[row * cols()];
    }

    const T* operator[](unsigned row) const
    {
        return &m_Values[row * cols()];
    }

    T* begin()
    {
        return m_Values.data();
    }

    T* end()
    {
        return m_Values.data() + size();
    }

    const T* begin() const
    {
        return m_Values.data();
    }

    const T* end() const
    {
        return m_Values.data() + size();
    }

    T* data()
    {
        return m_Values.data();
    }

    const T* data() const
    {
        return m_Values.data();
    }
private:
    std::array<T, N * N> m_Values;
};

}

#include "MatrixFunctions.hpp"
#include "MatrixOperators.hpp"

#endif
