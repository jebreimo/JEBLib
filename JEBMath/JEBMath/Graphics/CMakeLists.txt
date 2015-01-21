cmake_minimum_required(VERSION 2.8)

project(Graphics)

set(JEB_DIR JEBMath/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Color32.hpp
    Matrix.hpp
    MatrixFunctions.hpp
    MatrixOperators.hpp
    Transforms.hpp
    TransposedMatrix.hpp
    TransposedMatrixOperators.hpp
    Vector.hpp
    VectorFunctions.hpp
    VectorOperators.hpp
    )

set(SRC
    Color32.cpp
    Transforms.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS})

if (DEFINED JEB_INSTALL_JEBMATH_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBMATH_API)
