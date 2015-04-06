#ifndef JEBMATH_FRACTALS_SQUARESANDDIAMONDSGRIDS_HPP
#define JEBMATH_FRACTALS_SQUARESANDDIAMONDSGRIDS_HPP

#include "JEBBase/Containers/Array2D.hpp"

namespace JEBMath { namespace Fractals {

namespace SquaresAndDiamonds
{
    // class IGrid
    // {
    // public:
    //     virtual ~IGrid();

    //     virtual double getValue(int x, int y, size_t& n) const = 0;
    //     virtual void setValue(int x, int y, double value) = 0;

    //     virtual int getWidth() const = 0;
    //     virtual int getHeight() const = 0;
    // };

    class EnvelopedGrid //: IGrid
    {
    public:
        EnvelopedGrid(JEBBase::Containers::Array2D<double>& grid);

        double getValue(int x, int y, size_t& n) const;
        void setValue(int x, int y, double value);

        int getWidth() const;
        int getHeight() const;
    private:
        JEBBase::Containers::Array2D<double>& m_Grid;
    };

    class IslandGrid //: IGrid
    {
    public:
        IslandGrid(JEBBase::Containers::Array2D<double>& grid);

        double getValue(int x, int y, size_t& n) const;
        void setValue(int x, int y, double value);

        double getExteriorValue() const;
        void setExteriorValue(double value);

        int getWidth() const;
        int getHeight() const;
    private:
        JEBBase::Containers::Array2D<double>& m_Grid;
        double m_ExteriorValue;
    };

    class WrappingGrid //: IGrid
    {
    public:
        WrappingGrid(JEBBase::Containers::Array2D<double>& grid);

        double getValue(int x, int y, size_t& n) const;
        void setValue(int x, int y, double value);

        int getWidth() const;
        int getHeight() const;
    private:
        JEBBase::Containers::Array2D<double>& m_Grid;
    };
}

}}

#endif
