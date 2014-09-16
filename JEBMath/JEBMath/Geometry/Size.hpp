#ifndef JEB_MATH_SIZE_HPP
#define JEB_MATH_SIZE_HPP

#include "Vector.hpp"

namespace JEBMath { namespace Dim2 {

template <typename T>
class Size
{
public:
    Size()
        : m_Width(0),
          m_Height(0)
    {}

    Size(T width, T height)
        : m_Width(width),
          m_Height(height)
    {}

    template <typename U>
    Size(const Size<U>& size)
        : m_Width(size.width()),
          m_Height(size.height())
    {}

    template <typename U>
    Size& operator=(const Size<U>& size)
    {
        m_Width = size.width();
        m_Height = size.height();
        return *this;
    }

    T width() const;
    void setWidth(T width);

    T height() const;
    void setHeight(T height);

    Vector<T, 2> vector() const
    {
        return vector2(m_Width, m_Height);
    }
private:
    T m_Width;
    T m_Height;
};

template <typename T>
T Size<T>::width() const
{
    return m_Width;
}

template <typename T>
void Size<T>::setWidth(T width)
{
    m_Width = width;
}

template <typename T>
T Size<T>::height() const
{
    return m_Height;
}

template <typename T>
void Size<T>::setHeight(T height)
{
    m_Height = height;
}

}}

#endif
