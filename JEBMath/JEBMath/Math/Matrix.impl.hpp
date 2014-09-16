#include <stdexcept>
#include "MatrixAlgorithms.hpp"

namespace JEBMath {

template <typename T>
Matrix<T>::Matrix()
{
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : m_Values(rows, cols)
{
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T factor)
{
    for (iterator it = begin(); it != end(); ++it)
        *it *= factor;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& rhs)
{
    if (columns() != rhs.rows())
        throw std::invalid_argument("number of columns on left-hand side doesn't match number of rows on right-hand side.");
    if (columns() != rhs.columns())
        throw std::invalid_argument("right-hand side must be a square matrix");
    T* rowIt = begin();
    std::vector<T> row(columns());
    for (size_t i = 0; i < rows(); i++)
    {
        typename std::vector<T>::iterator it = row.begin();
        for (size_t j = 0; j < columns(); j++)
        {
            *it = 0;
            for (size_t k = 0; k < columns(); k++)
                *it += (*this)[i][k] * rhs[k][j];
            it++;
        }
        rowIt = std::copy(row.begin(), row.end(), rowIt);
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T factor)
{
    for (iterator it = begin(); it != end(); ++it)
        *it /= factor;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    if (size() != rhs.size())
        throw std::invalid_argument("size of right hand side matrix isn't the same as left hand side");
    const_iterator cit = rhs.begin();
    for (iterator it = begin(); it != end(); it++)
        *it += *cit++;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
    if (size() != rhs.size())
        throw std::invalid_argument("size of right hand side matrix isn't the same as left hand side");
    const_iterator cit = rhs.begin();
    for (iterator it = begin(); it != end(); it++)
        *it -= *cit++;
    return *this;
}

template <typename T>
const T* Matrix<T>::operator[](size_t n) const
{
    return m_Values[n];
}

template <typename T>
T* Matrix<T>::operator[](size_t n)
{
    return m_Values[n];
}

template <typename T>
size_t Matrix<T>::rows() const
{
    return m_Values.size().first;
}

template <typename T>
size_t Matrix<T>::columns() const
{
    return m_Values.size().second;
}

template <typename T>
std::pair<size_t, size_t> Matrix<T>::size() const
{
    return std::make_pair(rows(), columns());
}

template <typename T>
typename Matrix<T>::iterator Matrix<T>::begin()
{
    return m_Values.begin();
}

template <typename T>
typename Matrix<T>::iterator Matrix<T>::end()
{
    return m_Values.end();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return m_Values.begin();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const
{
    return m_Values.end();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::cbegin() const
{
    return m_Values.cbegin();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::cend() const
{
    return m_Values.cend();
}

template <typename T>
void Matrix<T>::identity()
{
    if (rows() != columns())
        throw std::logic_error("identity matrixes must be square");
    T* it = begin();
    if (begin() == end())
        return;
    *it++ = 1;
    for (size_t i = 1; i < rows(); i++)
    {
        for (size_t j = 0; j < columns(); j++)
            *it++ = 0;
        *it++ = 1;
    }
}

template <typename T>
void Matrix<T>::invert()
{
    if (rows() != columns())
        throw std::logic_error("Matrix isn't invertible");
    if (rows() > 1)
        throw std::logic_error(std::string(__func__) + " not implemented");
}

template <typename T>
void Matrix<T>::swap(Matrix& other)
{
    m_Values.swap(other.m_Values);
}

template <typename T>
void Matrix<T>::transpose()
{
    MatrixAlgorithms::transposeInPlace(m_Values.begin(), rows(), columns());
    m_Values.setSize(columns(), rows());
}

template <typename T>
void Matrix<T>::turn(size_t n)
{
    switch (n % 4)
    {
    case 1:
        MatrixAlgorithms::turnLeftInPlace(m_Values.begin(), rows(), columns());
        m_Values.setSize(columns(), rows());
        break;
    case 2:
        MatrixAlgorithms::turnUpsideDownInPlace(m_Values.begin(), rows(), columns());
        break;
    case 3:
        MatrixAlgorithms::turnRightInPlace(m_Values.begin(), rows(), columns());
        m_Values.setSize(columns(), rows());
        break;
    default:
        break;
    }
}

template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return lhs.rows() == rhs.rows() && lhs.columns() == rhs.columns() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& m)
{
    Matrix<T> n(m);
    for (auto it = n.begin(); it != n.end(); it++)
        *it = -*it;
    return n;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, T factor)
{
    Matrix<T> m(lhs);
    return m *= factor;
}

template <typename T>
Matrix<T> operator*(T factor, const Matrix<T>& lhs)
{
    return lhs * factor;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    Matrix<T> m(lhs.rows(), rhs.columns());
    multiply(m, lhs, rhs);
    return m;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    Matrix<T> m(lhs);
    return m += rhs;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    Matrix<T> m(lhs);
    return m -= rhs;
}

template <typename T>
Matrix<T> transposition(const Matrix<T>& m)
{
    Matrix<T> n(m.columns(), m.rows());
    for (size_t i = 0; i < m.rows(); i++)
        for (size_t j = 0; j < m.columns(); j++)
            n[j][i] = m[i][j];
    return n;
}

template <typename T>
void transpose(Matrix<T>& dst, const Matrix<T>& src)
{
    if (dst.size() != src.size())
        throw std::invalid_argument("destination's size doesn't match the size of source's transposition.");
    for (size_t i = 0; i < src.rows(); i++)
        for (size_t j = 0; j < src.columns(); j++)
            dst[j][i] = src[i][j];
}

template <typename T>
Matrix<T> invert(const Matrix<T>& m)
{
    Matrix<T> n(m.rows(), m.columns());
    invert(n, m);
    return n;
}

template <typename T>
void invert(Matrix<T>& dst, const Matrix<T>& src)
{
    if (src.rows() != src.columns())
        throw std::invalid_argument("matrix is not invertible");
    if (src.size() != dst.size())
        throw std::invalid_argument("destination's size differs from source's");
    throw std::logic_error(std::string(__func__) + " not implemented");
}

template <typename T>
void multiply(Matrix<T>& dst, const Matrix<T>& a, const Matrix<T>& b)
{
    if (a.columns() != b.rows())
        throw std::invalid_argument("number of columns on left-hand side doesn't match number of rows on right-hand side.");
    if (dst.rows() != a.rows() || dst.columns() != b.columns())
        throw std::invalid_argument("destination has incorrect size");
    for (size_t i = 0; i < dst.rows(); i++)
    {
        for (size_t j = 0; j < dst.columns(); j++)
        {
            T product = 0;
            for (size_t k = 0; k < a.columns(); k++)
                product += a[i][k] * b[k][j];
            dst[i][j] = product;
        }
    }
}

template <typename T>
void multiplyTransposition(Matrix<T>& dst,
                           const Matrix<T>& a,
                           const Matrix<T>& bt)
{
    if (a.columns() != bt.columns())
        throw std::invalid_argument("matrixes have different number of columns.");
    if (dst.rows() != a.rows() || dst.columns() != bt.rows())
        throw std::invalid_argument("destination has incorrect size");
    for (size_t i = 0; i < dst.rows(); i++)
    {
        for (size_t j = 0; j < dst.columns(); j++)
        {
            T product = 0;
            for (size_t k = 0; k < a.columns(); k++)
                dst[i][j] += a[i][k] * bt[j][k];
            dst[i][j] = product;
        }
    }
}

template <typename T>
Matrix<T> multiplyTransposition(const Matrix<T>& a, const Matrix<T>& bt)
{
    Matrix<T> dst(a.rows(), bt.rows());
    multiplyTransposition(dst, a, bt);
    return dst;
}

}
