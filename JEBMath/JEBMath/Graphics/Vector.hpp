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

    template <typename U>
    Vector(std::initializer_list<U> v)
    {
        if (v.size() != N)
            throw std::invalid_argument("Incorrect number of arguments.");
        auto it = v.begin();
        for (size_t i = 0; i < N; ++i)
            m_Values[i] = static_cast<T>(*it++);
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
private:
    std::array<T, N> m_Values;
};

}

#endif
