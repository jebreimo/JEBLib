#include "SquaresAndDiamondsGrids.hpp"

#include "Utilities.hpp"

namespace JEBMath { namespace Fractals {

namespace SquaresAndDiamonds
{
    // IGrid::~IGrid()
    // {}

    EnvelopedGrid::EnvelopedGrid(JEBBase::Containers::Array2D<double>& grid)
        : m_Grid(grid)
    {}

    double EnvelopedGrid::getValue(int x, int y, size_t& n) const
    {
        if (0 <= x && x < m_Grid.columns() && 0 <= y && y < m_Grid.rows())
        {
            ++n;
            return m_Grid[y][x];
        }
        else
        {
            return 0;
        }
    }

    void EnvelopedGrid::setValue(int x, int y, double value)
    {
        if (0 <= x && x < m_Grid.columns() && 0 <= y && y < m_Grid.rows())
            m_Grid[y][x] = value;
    }

    int EnvelopedGrid::getWidth() const
    {
        return (int)m_Grid.columns();
    }

    int EnvelopedGrid::getHeight() const
    {
        return (int)m_Grid.rows();
    }

    IslandGrid::IslandGrid(JEBBase::Containers::Array2D<double>& grid)
        : m_Grid(grid),
          m_ExteriorValue()
    {}

    double IslandGrid::getValue(int x, int y, size_t& n) const
    {
        ++n;
        if (0 <= x && x < m_Grid.columns() && 0 <= y && y < m_Grid.rows())
            return m_Grid[y][x];
        else
            return m_ExteriorValue;
    }

    void IslandGrid::setValue(int x, int y, double value)
    {
        if (0 <= x && x < m_Grid.columns() && 0 <= y && y < m_Grid.rows())
            m_Grid[y][x] = value;
    }

    double IslandGrid::getExteriorValue() const
    {
        return m_ExteriorValue;
    }

    void IslandGrid::setExteriorValue(double value)
    {
        m_ExteriorValue = value;
    }

    int IslandGrid::getWidth() const
    {
        return (int)m_Grid.columns();
    }

    int IslandGrid::getHeight() const
    {
        return (int)m_Grid.rows();
    }

    WrappingGrid::WrappingGrid(JEBBase::Containers::Array2D<double>& grid)
        : m_Grid(grid)
    {}

    double WrappingGrid::getValue(int x, int y, size_t& n) const
    {
        ++n;
        return m_Grid[modulo(y, m_Grid.rows())][modulo(x, m_Grid.columns())];
    }

    void WrappingGrid::setValue(int x, int y, double value)
    {
        m_Grid[modulo(y, m_Grid.rows())][modulo(x, m_Grid.columns())] = value;
    }

    int WrappingGrid::getWidth() const
    {
        return (int)m_Grid.columns() + 1;
    }
    int WrappingGrid::getHeight() const
    {
        return (int)m_Grid.rows() + 1;
    }
}

}}
