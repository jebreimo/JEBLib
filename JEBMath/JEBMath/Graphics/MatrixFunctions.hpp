#ifndef JEBMATH_GRAPHICS_MATRIXFUCTIONS_HPP
#define JEBMATH_GRAPHICS_MATRIXFUCTIONS_HPP

#include "JEBMath/Graphics/Matrix.hpp"

namespace JEBMath {

template <typename T, size_t N>
void transpose(Matrix<T, N>& m)
{
    for (auto i = 0u; i < N; ++i)
    {
        for (auto j = i + 1; j < N; ++j)
            std::swap(m[i][j], m[j][i]);
    }
}

template <typename T, size_t N>
Matrix<T, N> transposed(Matrix<T, N>& m)
{
    Matrix<T, N> t;
    for (auto i = 0u; i < N; ++i)
    {
        for (auto j = 0u; j < N; ++j)
            t[i][j] = m[j][i];
    }
    return t;
}

}

#endif
