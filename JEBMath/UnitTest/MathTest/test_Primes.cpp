#include "JEBMath/Math/Primes.hpp"
#include <JEBTest/JEBTest.hpp>

using JEBMath::nextPrime;
using JEBMath::firstFactor;
using JEBMath::computePrimes;

void test_NextPrime()
{
    JT_EQUAL(nextPrime(0), 2);
    JT_EQUAL(nextPrime(2), 3);
    JT_EQUAL(nextPrime(3), 5);
    JT_EQUAL(nextPrime(5), 7);
    JT_EQUAL(nextPrime(7), 11);
    JT_EQUAL(nextPrime(11), 13);
    JT_EQUAL(nextPrime(13), 17);
    JT_EQUAL(nextPrime(17), 19);
    JT_EQUAL(nextPrime(19), 23);
    JT_EQUAL(nextPrime(23), 29);
}

void test_NextFactor()
{
    int n = -32340;
    int factor = firstFactor(n);
    JT_EQUAL(factor, -1);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 2);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 2);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 3);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 5);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 7);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 7);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 11);
    n /= factor;
    factor = firstFactor(n, factor);
    JT_EQUAL(factor, 1);
}

void test_ComputePrimes()
{
    std::vector<int> ps = computePrimes(5, 5);
    JT_EQUAL(ps.size(), 5);
    JT_EQUAL(ps[0], 11);
    JT_EQUAL(ps[1], 13);
    JT_EQUAL(ps[2], 17);
    JT_EQUAL(ps[3], 19);
    JT_EQUAL(ps[4], 23);
}

JT_SUBTEST("Math", test_NextPrime, test_NextFactor, test_ComputePrimes);
