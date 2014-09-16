#ifndef JEB_MATH_PROFILEITERATOR_HPP
#define JEB_MATH_PROFILEITERATOR_HPP

#include "Types.hpp"

namespace JEBMath { namespace Dim2 {

class ProfileIterator
{
public:
    ProfileIterator(const LineStringD* prof, size_t* index);
    bool isValid() const;
    void next();

    size_t index() const;
    void setIndex(size_t index);

    const LineStringD* profile() const;

    double undefinedHeight() const;
    void setUndefinedHeight(double undefinedHeight);

    PointD point() const;
    PointD pointAtX(double x) const;
    double x() const;
    double y() const;
    double yAtX(double x) const;
    LineSegmentD segment() const;
private:
    const LineStringD* m_Profile;
    size_t* m_Index;
    double m_UndefinedHeight;
};

}}

#endif
