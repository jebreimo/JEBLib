#ifndef JEBMATH_GRAPHICS_VECTOR_HPP
#define JEBMATH_GRAPHICS_VECTOR_HPP

#include <initializer_list>
#include <stdexcept>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

template <typename T, size_t N>
class Vector
{
public:
    static const size_t Dimension = N;
    static const size_t dimension() {return N;}

    Vector()
    {
        for (int i = 0; i < N; ++i)
            m_Coords[i] = T();
    }

    Vector(std::initializer_list<T> v)
    {
        if (v.size() != N)
            throw std::invalid_argument("Incorrect number of arguments.");
        auto it = v.begin();
        for (int i = 0; i < N; ++i)
            m_Coords[i] = *it++;
    }

    Vector(T (&arr)[N])
    {
        for (int i = 0; i < N; ++i)
            m_Coords[i] = arr[i];
    }

    template <typename U>
    explicit Vector(const Vector<U, N>& other)
    {
        for (int i = 0; i < N; ++i)
            m_Coords[i] = other[i];
    }

    template <typename U>
    Vector<T, N>& operator=(const Vector<U, N>& other)
    {
        for (int i = 0; i < N; ++i)
            m_Coords[i] = other[i];
        return *this;
    }

    template <typename U>
    operator Vector<U, N>() const
    {
        return Vector<U, N>(*this);
    }

    explicit operator bool() const
    {
        for (int i = 0; i < N; ++i)
        {
            if (m_Coords[i])
                return true;
        }
        return false;
    }

    const T& operator[](size_t i) const
    {
        return m_Coords[i];
    }

    T& operator[](size_t i)
    {
        return m_Coords[i];
    }

    const T* begin() const
    {
        return &m_Coords[0];
    }

    T* begin()
    {
        return &m_Coords[0];
    }

    const T* end() const
    {
        return &m_Coords[N];
    }

    T* end()
    {
        return &m_Coords[N];
    }
private:
    T m_Coords[N];
};

}

#endif
