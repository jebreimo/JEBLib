#ifndef JEB_MATH_FRACTION_HPP
#define JEB_MATH_FRACTION_HPP

#include <iosfwd>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

template <typename T>
class Fraction
{
public:
    Fraction();
    explicit Fraction(T value);
    Fraction(T num, T den);

    T numerator() const;
    T denominator() const;
    void set(T numerator, T denominator);

    Fraction<T>& operator++();
    Fraction<T> operator++(int);
    Fraction<T>& operator--();
    Fraction<T> operator--(int);
    Fraction<T>& operator+=(const Fraction<T>& f);
    Fraction<T>& operator+=(T v);
    Fraction<T>& operator-=(const Fraction<T>& f);
    Fraction<T>& operator-=(T v);
    Fraction<T>& operator*=(const Fraction<T>& f);
    Fraction<T>& operator*=(T v);
    Fraction<T>& operator/=(const Fraction<T>& f);
    Fraction<T>& operator/=(T v);

    void invert();
private:
    void reduce();
    void ensureSign();
    T abs(T value);

    T m_Numerator;
    T m_Denominator;
};

template <typename T>
Fraction<T> inversion(const Fraction<T>& f);

template <typename T>
bool operator==(const Fraction<T>& a, const Fraction<T>& b);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Fraction<T>& f);

template <typename T>
Fraction<T> operator-(const Fraction<T>& f);

template <typename T>
Fraction<T> operator+(const Fraction<T>& a, const Fraction<T>& b);
template <typename T>
Fraction<T> operator+(const Fraction<T>& f, T v);
template <typename T>
Fraction<T> operator+(T v, const Fraction<T>& f);

template <typename T>
Fraction<T> operator-(const Fraction<T>& a, const Fraction<T>& b);
template <typename T>
Fraction<T> operator-(const Fraction<T>& f, T v);
template <typename T>
Fraction<T> operator-(T v, const Fraction<T>& f);

template <typename T>
Fraction<T> operator*(const Fraction<T>& a, const Fraction<T>& b);
template <typename T>
Fraction<T> operator*(const Fraction<T>& f, T v);
template <typename T>
Fraction<T> operator*(T v, const Fraction<T>& f);

template <typename T>
Fraction<T> operator/(const Fraction<T>& a, const Fraction<T>& b);
template <typename T>
Fraction<T> operator/(const Fraction<T>& f, T v);
template <typename T>
Fraction<T> operator/(T v, const Fraction<T>& f);

}

#include "Fraction.impl.hpp"

#endif
