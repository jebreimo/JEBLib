#include "SquaresAndDiamonds.hpp"

#include <algorithm>
#include <random>
#include "JEBBase/Bits/Bits.hpp"
#include "JEBMath/Math/Random.hpp"
#include "JEBMath/Math/Utilities.hpp"

namespace JEBMath { namespace Fractals {

namespace
{
    typedef double (*GetValueFunc)(JEBBase::Containers::Array2D<double>&,
                                   int i, int j, int& counter);

    double getGridValue(JEBBase::Containers::Array2D<double>& grid,
                        int i, int j, int& counter)
    {
        if (0 <= i && i < grid.rows() && 0 <= j && j < grid.columns())
        {
            ++counter;
            return grid[i][j];
        }
        else
        {
            return 0;
        }
    }

    double getIslandGridValue(JEBBase::Containers::Array2D<double>& grid,
                              int i, int j, int& counter)
    {
        ++counter;
        if (0 <= i && i < grid.rows() && 0 <= j && j < grid.columns())
            return grid[i][j];
        else
            return 0;
    }

    double getWrappedGridValue(JEBBase::Containers::Array2D<double>& grid,
                               int i, int j, int& counter)
    {
        ++counter;
        return grid[modulo(i, grid.rows())][modulo(j, grid.columns())];
    }

    GetValueFunc getGetValueFunc(GridMode gridMode)
    {
        switch (gridMode)
        {
        case NORMAL_GRID_MODE: return getGridValue;
        case WRAPPED_GRID_MODE: return getWrappedGridValue;
        case ISLAND_GRID_MODE: return getIslandGridValue;
        default: return getGridValue;
        }
    }

    double computeValue(JEBBase::Containers::Array2D<double>& grid,
                        GetValueFunc getValueFunc,
                        int i, int j, int offset1, int offset2)
    {
        auto n = 0;
        auto sum = getValueFunc(grid, i - offset2, j - offset1, n) +
                   getValueFunc(grid, i - offset1, j + offset2, n) +
                   getValueFunc(grid, i + offset1, j - offset2, n) +
                   getValueFunc(grid, i + offset2, j + offset1, n);
        return sum / n;
    }

    void computeValues(JEBBase::Containers::Array2D<double>& grid,
                       GetValueFunc getValueFunc,
                       RandomRealGenerator<double>& rng,
                       int i0, int j0, int offset1, int offset2,
                       int stepSize)
    {
        for (auto i = i0; i < grid.rows(); i += stepSize)
            for (auto j = j0; j < grid.columns(); j += stepSize)
                grid[i][j] = computeValue(grid, getValueFunc,
                                          i, j, offset1, offset2) +
                             rng.generate();
    }

    void fillSquares(JEBBase::Containers::Array2D<double>& grid,
                     GetValueFunc getValueFunc,
                     RandomRealGenerator<double>& rng,
                     int stepSize)
    {
        auto v = stepSize / 2;
        computeValues(grid, getValueFunc, rng, v, v, v, v, stepSize);
    }

    void fillDiamonds1(JEBBase::Containers::Array2D<double>& grid,
                       GetValueFunc getValueFunc,
                       RandomRealGenerator<double>& rng,
                       int stepSize)
    {
        auto v = stepSize / 2;
        computeValues(grid, getValueFunc, rng, v, 0, v, 0, stepSize);
    }

    void fillDiamonds2(JEBBase::Containers::Array2D<double>& grid,
                       GetValueFunc getValueFunc,
                       RandomRealGenerator<double>& rng,
                       int stepSize)
    {
        auto v = stepSize / 2;
        computeValues(grid, getValueFunc, rng, 0, v, v, 0, stepSize);
    }

    void fillValues(JEBBase::Containers::Array2D<double>& grid,
                    GetValueFunc getValueFunc,
                    double randMax, int stepSize)
    {
        RandomRealGenerator<double> rng(-randMax, randMax);
        fillSquares(grid, getValueFunc, rng, stepSize);
        fillDiamonds1(grid, getValueFunc, rng, stepSize);
        fillDiamonds2(grid, getValueFunc, rng, stepSize);
    }

    void initialize(JEBBase::Containers::Array2D<double>& grid,
                    double randMax, int stepSize)
    {
        RandomRealGenerator<double> rng(-randMax, randMax);
        for (int i = 0; i < (int)grid.rows(); i += stepSize)
            for (int j = 0; j < (int)grid.columns(); j += stepSize)
                grid[i][j] = rng.generate();
    }

    void computeSquaresAndDiamonds(JEBBase::Containers::Array2D<double>& grid,
                                   GetValueFunc getValueFunc,
                                   double roughness, double randMax,
                                   int maxStepSize, int minStepSize)
    {
        for (auto stepSize = maxStepSize;
             stepSize > minStepSize;
             stepSize >>= 1)
        {
            fillValues(grid, getValueFunc, randMax, stepSize);
            randMax *= roughness;
        }
    }
}

void fillValues(
        JEBBase::Containers::Array2D<double>& grid,
        double randMax, int stepSize,
        GridMode gridMode)
{
    fillValues(grid, getGetValueFunc(gridMode), randMax, stepSize);
}

void computeSquaresAndDiamonds(
        JEBBase::Containers::Array2D<double>& grid,
        GridMode gridMode,
        double roughness,
        int maxStepSize, int minStepSize)
{
    auto randMax = 100.0;
    if (maxStepSize <= 0)
    {
        maxStepSize = (int)std::max(grid.rows(), grid.columns());
        maxStepSize = JEBBase::Bits::powerOfTwoFloor(maxStepSize);
        initialize(grid, randMax * 2, maxStepSize);
    }
    else
    {
        maxStepSize = JEBBase::Bits::powerOfTwoFloor(maxStepSize);
    }
    if (minStepSize < 1)
        minStepSize = 1;
    minStepSize = JEBBase::Bits::powerOfTwoCeiling(minStepSize);
    computeSquaresAndDiamonds(grid, getGetValueFunc(gridMode),
                              roughness, randMax, maxStepSize, minStepSize);
}

}}
