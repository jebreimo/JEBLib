#ifndef JEBMATH_GRAPHICS_TRANSPOSEDMATRIX_HPP
#define JEBMATH_GRAPHICS_TRANSPOSEDMATRIX_HPP

#include "Matrix.hpp"

namespace JEBMath {

template <typename T, size_t N>
class TransposedMatrix : public Matrix<T, N>
{
public:
    TransposedMatrix()
    {}

    TransposedMatrix(std::initializer_list<T> v)
        : Matrix<T, N>(v)
    {}

    template <typename U>
    TransposedMatrix(U (&arr)[N * N])
        : Matrix<T, N>(arr)
    {}

    explicit TransposedMatrix(const Matrix<T, N>& other)
        : Matrix<T, N>(other)
    {}
};

}

#endif
