#include "JEBBase/Bits/BitSet.hpp"

namespace JEBMath { namespace MatrixAlgorithms {

namespace
{
    template <typename RndIt, typename NextIndexFunc>
    void foo(RndIt matrix, size_t size, NextIndexFunc nextIndexFunc)
    {
        JEBBase::Bits::BitSet visited(size);
        auto unvisited = size_t{0};
        while (unvisited != JEBBase::Bits::BitSet::NotFound)
        {
            auto index = unvisited;
            auto value = std::move(matrix[index]);
            while (true)
            {
                visited.setBit(index, true);
                auto nextIndex = nextIndexFunc(index);
                if (visited.bit(nextIndex))
                    break;
                matrix[index] = std::move(matrix[nextIndex]);
                index = nextIndex;
            }
            matrix[index] = std::move(value);
            unvisited = visited.findFirst(false, unvisited + 1);
        }
    }

    size_t calculateIndex(size_t i, size_t j, size_t cols)
    {
        return i * cols + j;
    }
}

template <typename RndIt>
void transposeInPlace(RndIt matrix, size_t rows, size_t cols)
{
    return foo(matrix, rows * cols,
            [&](size_t n){return calculateIndex(n % rows, n / rows, cols);});
}

template <typename RndIt>
void turnLeftInPlace(RndIt matrix, size_t rows, size_t cols)
{
    return foo(matrix, rows * cols,
               [&](size_t n)
               {return calculateIndex(n % rows, cols - 1 - n / rows, cols);});
}

template <typename RndIt>
void turnRightInPlace(RndIt matrix, size_t rows, size_t cols)
{
    return foo(matrix, rows * cols,
               [&](size_t n)
               {return calculateIndex(rows - 1 - n % rows, n / rows, cols);});
}

template <typename RndIt>
void turnUpsideDownInPlace(RndIt matrix, size_t rows, size_t cols)
{
    return foo(matrix, rows * cols,
               [&](size_t n)
               {return calculateIndex(rows - 1 - n / rows,
                                      cols - 1 - n % rows, cols);});
}

}}
