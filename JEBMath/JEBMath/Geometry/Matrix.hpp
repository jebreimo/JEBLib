#ifndef JEBMATH_GEOMETRY_MATRIX_HPP
#define JEBMATH_GEOMETRY_MATRIX_HPP

#include <array>
#include <initializer_list>
#include <stdexcept>

namespace JEBMath {

template <typename T, size_t N>
class Matrix
{
public:
    static constexpr size_t rows() {return N;}
    static constexpr size_t cols() {return N;}
    static constexpr size_t size() {return N * N;}

    Matrix()
    {}

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

    T* operator[](size_t row)
    {
        return &m_Values[row * cols()];
    }

    const T* operator[](size_t row) const
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

#endif
