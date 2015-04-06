#include "JEBMath/Math/SquaresAndDiamonds.hpp"

#include <algorithm>
#include <JEBTest/JEBTest.hpp>

namespace {

const double DUMMY_VALUE = 10000;

void testValues(JEBBase::Containers::Array2D<double>& grid, size_t stepSize)
{
    for (auto i = 0U; i != grid.rows(); ++i)
    {
        if (i % stepSize)
        {
            for (auto j = 0U; j != grid.columns(); ++j)
                JT_EQUAL(grid[i][j], DUMMY_VALUE);
        }
        else
        {
            for (auto j = 0U; j != grid.columns(); ++j)
            {
                if (j % stepSize)
                    JT_EQUAL(grid[i][j], DUMMY_VALUE);
                else
                    JT_NOT_EQUAL(grid[i][j], DUMMY_VALUE);
            }
        }
    }
}

void testStepSizes(JEBBase::Containers::Array2D<double>& grid,
                   int maxStepSize, int minStepSize)
{
    std::fill(begin(grid), end(grid), DUMMY_VALUE);
    grid[0][0] = grid[0][grid.columns() - 1] =
                 grid[grid.rows() - 1][0] =
                 grid[grid.rows() - 1][grid.columns() - 1] = 100;
    JEBMath::Fractals::computeSquaresAndDiamonds(
            grid, JEBMath::Fractals::NORMAL_GRID_MODE,
            0.5, maxStepSize, minStepSize);
    JT_CALL(testValues(grid, minStepSize));
}

void test_computeSquaresAndDiamonds()
{
    JEBBase::Containers::Array2D<double> grid(9, 9);
    JT_CALL(testStepSizes(grid, 0, 8));
    JT_CALL(testStepSizes(grid, 0, 4));
    JT_CALL(testStepSizes(grid, 0, 2));
    JT_CALL(testStepSizes(grid, 0, 1));
}

JT_TEST(test_computeSquaresAndDiamonds);

}
