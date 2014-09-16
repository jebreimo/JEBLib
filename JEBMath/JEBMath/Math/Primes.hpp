#ifndef JEB_MATH_PRIMES_HPP
#define JEB_MATH_PRIMES_HPP

#include <vector>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

template <typename T>
bool isPrime(T n)
{
    if (n <= 1)
        return false;
    else if (n <= 3)
        return true;
    else if (n % 2 == 0)
        return false;
    T factor = 3;
    while (true)
    {
        if (n % factor == 0)
            return false;
        else if (n / factor <= factor)
            return true;
        factor += 2;
    }
}

template <typename T>
T nextPrime(T prevPrime = 0)
{
    if (prevPrime < 2)
        return 2;
    else if (prevPrime == 2)
        return 3;

    T prime = (prevPrime & 1) ? prevPrime + 2 : prevPrime + 1;
    if (prime % 3 == 0)
        prime += 2;
    T increment = (prime + 1) % 3 ? 4 : 2;
    while (!isPrime(prime))
    {
        prime += increment;
        increment = 6 - increment;
    }
    return prime;
}

/** @brief Returns the nth prime where @a n is one-based.
 */
template <typename T>
T nthPrime(T n)
{
    T prime = 0;
    for (T i = 0; i < n; i++)
        prime = nextPrime(prime);
    return prime;
}

/** @brief Returns @a count primes starting with the @a nth prime.
 */
template <typename T>
std::vector<T> computePrimes(T nth, T count)
{
    std::vector<T> primes;
    if (count > 0)
    {
        primes.push_back(nthPrime(nth));
        for (T i = 1; i < count; i++)
            primes.push_back(nextPrime(primes.back()));
    }
    return primes;
}

template <typename T>
T firstFactor(T n, T minFactor = 2)
{
    if (n < 0)
        return -1;
    else if (n <= 3)
        return n;

    if (minFactor < 2)
        minFactor = 2;
    if (n % minFactor == 0)
        return minFactor;
    minFactor |= 1; // Make sure minFactor is odd.
    while (true)
    {
        if (n % minFactor == 0)
            return minFactor;
        else if (n / minFactor <= minFactor)
            return n;
        minFactor += 2;
    }
}

template <typename T>
class Factorizer
{
public:
    Factorizer(T value)
        : m_Value(value),
          m_Factor(0),
          m_Increment(2)
    {
    }

    T next()
    {
        if (m_Factor < 5)
        {
            if (m_Value < 0)
            {
                m_Value = -m_Value;
                m_Factor = (T)-1;
                return (T)-1;
            }
            else if (m_Value % 2 == 0)
            {
                m_Value /= 2;
                m_Factor = 2;
                return 2;
            }
            else if (m_Value % 3 == 0)
            {
                m_Value /= 3;
                m_Factor = 3;
                return 3;
            }
            m_Factor = 5;
        }
        while (m_Value % m_Factor != 0)
        {
            if (m_Value / m_Factor <= m_Factor)
            {
                m_Factor = m_Value;
                break;
            }
            m_Factor += m_Increment;
            m_Increment = 6 - m_Increment;
        }
        m_Value /= m_Factor;
        return m_Factor;
    }

    T currentFactor() const
    {
        return m_Factor;
    }

    T remainder() const
    {
        return m_Value;
    }
private:
    T m_Value;
    T m_Factor;
    T m_Increment;
};

}

#endif
