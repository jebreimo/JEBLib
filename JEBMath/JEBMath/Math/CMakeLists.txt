cmake_minimum_required(VERSION 2.8)

project(Math)

set(JEB_DIR JEBMath/${PROJECT_NAME})

set(PUBLIC_HEADERS
    ArrayMath.hpp
    Binomial.hpp
    Combinations.hpp
    Comparisons.hpp
    Constants.hpp
    CubicFunction.hpp
    Fraction.hpp
    Fraction.impl.hpp
    FresnelIntegrals.hpp
    Limits.hpp
    MathAlgorithms.hpp
    Matrix.hpp
    Matrix.impl.hpp
    MatrixAlgorithms.hpp
    MatrixAlgorithms.impl.hpp
    Primes.hpp
    Random.hpp
    Rational.hpp
    Subset.hpp
    Utilities.hpp
    )

set(PRIVATE_HEADERS
    SquaresAndDiamonds.hpp
    )

set(SRC
    CubicFunction.cpp
    FresnelIntegrals.cpp
    Random.cpp
    SquaresAndDiamonds.cpp
    Subset.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC}
                                   ${PUBLIC_HEADERS}
                                   ${PRIVATE_HEADERS})

if (DEFINED JEB_INSTALL_JEBMATH_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBMATH_API)
