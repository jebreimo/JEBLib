#ifndef JEB_MATH_MATRIXALGORITHM_HPP
#define JEB_MATH_MATRIXALGORITHM_HPP

#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath { namespace MatrixAlgorithms {

template <typename RndIt>
void transposeInPlace(RndIt matrix, size_t rows, size_t cols);

template <typename RndIt>
void turnLeftInPlace(RndIt matrix, size_t rows, size_t cols);

template <typename RndIt>
void turnRightInPlace(RndIt matrix, size_t rows, size_t cols);

template <typename RndIt>
void turnUpsideDownInPlace(RndIt matrix, size_t rows, size_t cols);

}}

#include "MatrixAlgorithms.impl.hpp"

#endif
