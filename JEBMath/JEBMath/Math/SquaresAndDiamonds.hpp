#ifndef JEBMATH_FRACTALS_SQUARESANDDIAMONDS_HPP
#define JEBMATH_FRACTALS_SQUARESANDDIAMONDS_HPP

#include "JEBBase/Containers/Array2D.hpp"

namespace JEBMath { namespace Fractals {

enum GridMode
{
    NORMAL_GRID_MODE,
    WRAPPED_GRID_MODE,
    ISLAND_GRID_MODE
};

void fillValues(
        JEBBase::Containers::Array2D<double>& grid,
        double randMax, int stepSize,
        GridMode gridMode = NORMAL_GRID_MODE);

void computeSquaresAndDiamonds(
        JEBBase::Containers::Array2D<double>& grid,
        GridMode gridMode = NORMAL_GRID_MODE,
        double roughness = 0.5,
        int maxStepSize = 0, int minStepSize = 1);

}}

#endif
