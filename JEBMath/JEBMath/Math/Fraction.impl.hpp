#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ostream>
#include "Rational.hpp"

namespace JEBMath {

template <typename T>
Fraction<T>::Fraction()
    : m_Numerator(0),
      m_Denominator(1)
{
}

template <typename T>
Fraction<T>::Fraction(T value)
    : m_Numerator(value),
      m_Denominator(1)
{
}

template <typename T>
Fraction<T>::Fraction(T num, T den)
    : m_Numerator(num),
      m_Denominator(den)
{
    reduce();
}

template <typename T>
T Fraction<T>::numerator() const
{
    return m_Numerator;
}

template <typename T>
T Fraction<T>::denominator() const
{
    return m_Denominator;
}

template <typename T>
void Fraction<T>::set(T numerator, T denominator)
{
    m_Numerator = numerator;
    m_Denominator = denominator;
    reduce();
}

template <typename T>
Fraction<T>& Fraction<T>::operator++()
{
    m_Numerator += m_Denominator;
    return *this;
}

template <typename T>
Fraction<T> Fraction<T>::operator++(int)
{
    Fraction<T> tmp = *this;
    m_Numerator += m_Denominator;
    return tmp;
}

template <typename T>
Fraction<T>& Fraction<T>::operator--()
{
    m_Numerator -= m_Denominator;
    return *this;
}

template <typename T>
Fraction<T> Fraction<T>::operator--(int)
{
    Fraction<T> tmp = *this;
    m_Numerator -= m_Denominator;
    return tmp;
}

template <typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& f)
{
    T cd = gcd(m_Denominator, f.m_Denominator);
    if (cd > 1)
    {
        m_Numerator = m_Numerator * (f.m_Denominator / cd) +
                      f.m_Numerator * (m_Denominator / cd);
        m_Denominator *= f.m_Denominator / cd;
    }
    reduce();
    assert(m_Denominator >= 0);
    return *this;
}

template <typename T>
Fraction<T>& Fraction<T>::operator+=(T v)
{
    m_Numerator += v * m_Denominator;
    return *this;
}

template <typename T>
Fraction<T>& Fraction<T>::operator-=(const Fraction<T>& f)
{
    return *this += -f;
}

template <typename T>
Fraction<T>& Fraction<T>::operator-=(T v)
{
    m_Numerator -= v * m_Denominator;
    return *this;
}

template <typename T>
Fraction<T>& Fraction<T>::operator*=(const Fraction<T>& f)
{
    T cd1 = gcd(abs(m_Numerator), f.m_Denominator);
    T cd2 = gcd(abs(f.m_Numerator), m_Denominator);
    m_Numerator /= cd1;
    m_Denominator /= cd2;
    m_Numerator *= f.m_Numerator / cd2;
    m_Denominator *= f.m_Denominator / cd1;
    assert(m_Denominator >= 0);
    return *this;
}

template <typename T>
Fraction<T>& Fraction<T>::operator*=(T v)
{
    T cd = gcd(abs(v), m_Denominator);
    m_Denominator /= cd;
    m_Numerator *= m_Numerator / cd;
    assert(m_Denominator >= 0);
    return *this;
}

template <typename T>
Fraction<T>& Fraction<T>::operator/=(const Fraction<T>& f)
{
    return *this *= inversion(f);
}

template <typename T>
Fraction<T>& Fraction<T>::operator/=(T v)
{
    return *this *= Fraction(1, v);
}

template <typename T>
void Fraction<T>::invert()
{
    std::swap(m_Numerator, m_Denominator);
    ensureSign();
}

template <typename T>
void Fraction<T>::reduce()
{
    ensureSign();
    reduceFraction(m_Numerator, m_Denominator);
}

template <typename T>
void Fraction<T>::ensureSign()
{
    if (m_Denominator < 0)
    {
        m_Denominator = -m_Denominator;
        m_Numerator = -m_Numerator;
    }
}

template <>
inline void Fraction<unsigned>::ensureSign()
{
}

template <>
inline void Fraction<unsigned long>::ensureSign()
{
}

template <typename T>
T Fraction<T>::abs(T value)
{
    return std::abs(value);
}

template <>
inline unsigned Fraction<unsigned>::abs(unsigned value)
{
    return value;
}

template <>
inline unsigned long Fraction<unsigned long>::abs(unsigned long value)
{
    return value;
}

template <typename T>
Fraction<T> inversion(const Fraction<T>& f)
{
    Fraction<T> g = f;
    g.invert();
    return g;
}

template <typename T>
bool operator==(const Fraction<T>& a, const Fraction<T>& b)
{
    return a.numerator() == b.numerator() &&
           a.denominator() == b.denominator();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Fraction<T>& f)
{
    os << f.numerator();
    if (f.denominator() != 1)
        os << "/" << f.denominator();
    return os;
}

template <typename T>
Fraction<T> operator-(const Fraction<T>& f)
{
    return Fraction<T>(-f.numerator(), f.denominator());
}

template <typename T>
Fraction<T> operator+(const Fraction<T>& a, const Fraction<T>& b)
{
    Fraction<T> tmp = a;
    return tmp += b;
}

template <typename T>
Fraction<T> operator+(const Fraction<T>& f, T v)
{
    Fraction<T> tmp = f;
    return tmp += v;
}

template <typename T>
Fraction<T> operator+(T v, const Fraction<T>& f)
{
    Fraction<T> tmp = f;
    return tmp += v;
}

template <typename T>
Fraction<T> operator-(const Fraction<T>& a, const Fraction<T>& b)
{
    Fraction<T> tmp = a;
    return tmp -= b;
}

template <typename T>
Fraction<T> operator-(const Fraction<T>& f, T v)
{
    Fraction<T> tmp = f;
    return tmp -= v;
}

template <typename T>
Fraction<T> operator-(T v, const Fraction<T>& f)
{
    Fraction<T> tmp = f;
    return tmp -= v;
}

template <typename T>
Fraction<T> operator*(const Fraction<T>& a, const Fraction<T>& b)
{
    Fraction<T> tmp = a;
    return tmp *= b;
}

template <typename T>
Fraction<T> operator*(const Fraction<T>& f, T v)
{
    Fraction<T> tmp = f;
    return tmp *= v;
}

template <typename T>
Fraction<T> operator*(T v, const Fraction<T>& f)
{
    Fraction<T> tmp = f;
    return tmp *= v;
}

template <typename T>
Fraction<T> operator/(const Fraction<T>& a, const Fraction<T>& b)
{
    Fraction<T> tmp = a;
    return tmp /= b;
}

template <typename T>
Fraction<T> operator/(const Fraction<T>& f, T v)
{
    Fraction<T> tmp = f;
    return tmp /= v;
}

template <typename T>
Fraction<T> operator/(T v, const Fraction<T>& f)
{
    Fraction<T> tmp(v);
    return tmp /= f;
}

}
