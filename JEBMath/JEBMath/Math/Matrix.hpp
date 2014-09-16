#ifndef JEB_MATH_MATRIX_HPP
#define JEB_MATH_MATRIX_HPP

#include <algorithm>
#include "JEBBase/Containers/Array2D.hpp"

namespace JEBMath {

template <typename T>
class Matrix
{
public:
    typedef typename JEBBase::Containers::Array2D<T>::iterator iterator;
    typedef typename JEBBase::Containers::Array2D<T>::const_iterator
        const_iterator;

    Matrix();
    Matrix(size_t rows, size_t cols);

    Matrix& operator*=(T factor);
    Matrix& operator*=(const Matrix& rhs);
    Matrix& operator/=(T factor);
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);

    const T* operator[](size_t n) const;
    T* operator[](size_t n);

    size_t rows() const;
    size_t columns() const;

    /** @brief Returns a pair (rows, columns).
     *
     *  This is a convenient function when comparing matrix sizes.
     */
    std::pair<size_t, size_t> size() const;

    template <typename It>
    void copyRow(size_t row, It dest)
    {
        std::copy(begin() + row * columns(),
                  begin() + (row + 1) * columns(),
                  dest);
    }

    template <typename It>
    void copyColumn(size_t col, It dest)
    {
        for (const_iterator it = begin() + col; it < end(); it += columns())
            *dest++ = *it;
    }

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    void identity();
    void invert();
    void swap(Matrix& other);
    void transpose();

    /** @brief Rotates the values in the matrix to the left @a n times.
     */
    void turn(size_t n);
private:
    JEBBase::Containers::Array2D<T> m_Values;
};

template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator-(const Matrix<T>& m);
template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, T factor);
template <typename T>
Matrix<T> operator*(T factor, const Matrix<T>& lhs);
template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <typename T>
Matrix<T> transposition(const Matrix<T>& m);
template <typename T>
void transpose(Matrix<T>& dst, const Matrix<T>& src);

template <typename T>
Matrix<T> invert(const Matrix<T> m);
template <typename T>
void invert(Matrix<T>& dst, const Matrix<T>& src);
template <typename T>
void multiply(Matrix<T>& dst, const Matrix<T>& a, const Matrix<T>& b);
template <typename T>
void multiplyTransposition(Matrix<T>& dst,
                           const Matrix<T>& a,
                           const Matrix<T>& bt);
template <typename T>
Matrix<T> multiplyTransposition(const Matrix<T>& a, const Matrix<T>& bt);

}

#include "Matrix.impl.hpp"

#endif
