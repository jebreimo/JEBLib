#include "JEBMath/Graphics/Matrix.hpp"
#include "JEBMath/Graphics/TransposedMatrix.hpp"
#include "JEBMath/Graphics/Vector.hpp"

namespace JEBMath {

template <typename T, typename U, size_t N>
auto operator*(Matrix<T, N>& a, const TransposedMatrix<U, N>& b)
    -> Matrix<decltype(T() * U()), N>
{
    typedef decltype(T() * U()) ResType;
    Matrix<ResType, N> c;
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            ResType v = 0;
            for (size_t k = 0; k < N; ++k)
                v += a[i][k] * b[j][k];
            c[i][j] = v;
        }
    }
    return c;
}

template <typename T, typename U, size_t N>
Matrix<T, N>& operator*=(Matrix<T, N>& a, const TransposedMatrix<U, N>& b)
{
    return a = a * b;
}

}
