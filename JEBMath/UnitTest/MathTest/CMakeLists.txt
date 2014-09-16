cmake_minimum_required(VERSION 2.8)

project(MathTest)

set(SRC
    test_Binomial.cpp
    test_Combinations.cpp
    test_CubicFunction.cpp
    test_Fraction.cpp
    test_Matrix.cpp
    test_Primes.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
