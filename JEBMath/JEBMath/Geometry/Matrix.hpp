#ifndef JEBMATH_GEOMETRY_MATRIX_HPP
#define JEBMATH_GEOMETRY_MATRIX_HPP

namespace JEBMath
{

template <typename T, size_t N>
class Matrix
{
public:
    constexpr size_t rows() {return N;}
    constexpr size_t columns() {return N;}

    const T* operator[](size_t row) const {return m_Values + (row * N);}
    T* operator[](size_t row) {return m_Values + (row * N);}
private:
    T m_Values[N * N];
};

}

#endif
