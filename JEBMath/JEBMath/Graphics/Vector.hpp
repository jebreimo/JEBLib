#ifndef JEBMATH_GRAPHICS_VECTOR_HPP
#define JEBMATH_GRAPHICS_VECTOR_HPP

#include <array>
#include <initializer_list>
#include <stdexcept>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

template <typename T, size_t N>
class Vector
{
public:
    typedef T ValueType;
    static constexpr size_t size() {return N;}

    Vector()
    {}

    Vector(std::initializer_list<T> v)
    {
        if (v.size() != N)
            throw std::invalid_argument("Incorrect number of arguments.");
        auto it = v.begin();
        for (size_t i = 0; i < N; ++i)
            m_Values[i] = *it++;
    }

    template <typename U>
    Vector(U (&arr)[N])
    {
        for (int i = 0; i < N; ++i)
            m_Values[i] = arr[i];
    }

    template <typename U, size_t M>
    Vector(const Vector<U, M>& other)
    {
        size_t i = 0;
        for (; i < std::min(N, M); ++i)
            m_Values[i] = other[i];
        for (; i < N; ++i)
            m_Values[i] = T();
    }

    template <typename U>
    Vector& operator=(U (&arr)[N])
    {
        for (int i = 0; i < N; ++i)
            m_Values[i] = arr[i];
        return *this;
    }

    template <typename U, size_t M>
    Vector& operator=(const Vector<U, N>& other)
    {
        size_t i = 0;
        for (; i < std::min(N, M); ++i)
            m_Values[i] = other[i];
        for (; i < N; ++i)
            m_Values[i] = T();
        return *this;
    }

    template <typename U>
    operator Vector<U, N>() const
    {
        return Vector<U, N>(*this);
    }

    explicit operator bool() const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (m_Values[i])
                return true;
        }
        return false;
    }

    const T& operator[](size_t i) const
    {
        return m_Values[i];
    }

    T& operator[](size_t i)
    {
        return m_Values[i];
    }

    const T* begin() const
    {
        return &m_Values[0];
    }

    T* begin()
    {
        return &m_Values[0];
    }

    const T* end() const
    {
        return &m_Values[N];
    }

    T* end()
    {
        return &m_Values[N];
    }

    T* data()
    {
        return &m_Values[0];
    }

    const T* data() const
    {
        return &m_Values[0];
    }
private:
    std::array<T, N> m_Values;
};

template <typename T, size_t N>
const T* begin(const Vector<T, N>& v)
{
    return v.begin();
}

template <typename T, size_t N>
const T* end(const Vector<T, N>& v)
{
    return v.end();
}

template <typename T, size_t N>
T* begin(Vector<T, N>& v)
{
    return v.begin();
}

template <typename T, size_t N>
T* end(Vector<T, N>& v)
{
    return v.end();
}

template <typename T>
Vector<T, 2> vector2(T x, T y)
{
    return Vector<T, 2>({x, y});
}

template <typename T>
Vector<T, 3> vector3(T x, T y, T z)
{
    return Vector<T, 3>({x, y, z});
}

template <typename T>
Vector<T, 4> vector4(T x, T y, T z, T w)
{
    return Vector<T, 4>({x, y, z, w});
}

template <typename T, typename U, size_t N>
Vector<T, N> vector(const Vector<U, N>& v)
{
    return Vector<T, N>(v);
}

}

#endif
