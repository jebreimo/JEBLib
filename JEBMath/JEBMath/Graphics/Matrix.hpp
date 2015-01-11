#ifndef JEBMATH_GRAPHICS_MATRIX_HPP
#define JEBMATH_GRAPHICS_MATRIX_HPP

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

    template <typename U>
    Matrix(std::initializer_list<U> v)
    {
        if (v.size() != size())
            throw std::invalid_argument("Incorrect number of arguments.");
        auto it = v.begin();
        for (size_t i = 0; i < size(); ++i)
            m_Values[i] = (T)*it++;
    }

    template <typename U>
    Matrix(U (&arr)[size()])
    {
        for (size_t i = 0; i < size(); ++i)
            m_Values[i] = arr[i];
    }

    template <typename U>
    explicit Matrix(const Matrix<U, N>& other)
    {
        for (size_t i = 0; i < size(); ++i)
            m_Values[i] = other[i];
    }


    template <typename U>
    Matrix<T, N>& operator=(const Matrix<U, N>& other)
    {
        auto it = begin(other);
        for (size_t i = 0; i < size(); ++i)
            m_Values[i] = (T)*it++;
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

private:
    std::array<T, N * N> m_Values;
};

}

#endif
