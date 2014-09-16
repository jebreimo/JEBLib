#include "ProfileIterator.hpp"

#include <limits>
#include "JEBMath/Math/Constants.hpp"
#include "Profile.hpp"

namespace JEBMath { namespace Dim2 {

using namespace std;

ProfileIterator::ProfileIterator(const LineStringD* prof, size_t* index)
    : m_Profile(prof),
      m_Index(index),
      m_UndefinedHeight(numeric_limits<double>::max())
{
}

bool ProfileIterator::isValid() const
{
    return *m_Index != m_Profile->size();
}

void ProfileIterator::next()
{
    if (*m_Index != m_Profile->size())
        ++(*m_Index);
}

size_t ProfileIterator::index() const
{
    return *m_Index;
}

void ProfileIterator::setIndex(size_t index)
{
    *m_Index = std::min(index, m_Profile->size());
}

const LineStringD* ProfileIterator::profile() const
{
    return m_Profile;
}

double ProfileIterator::undefinedHeight() const
{
    return m_UndefinedHeight;
}

void ProfileIterator::setUndefinedHeight(double undefinedHeight)
{
    m_UndefinedHeight = undefinedHeight;
}

PointD ProfileIterator::point() const
{
    return (*m_Profile)[*m_Index];
}

PointD ProfileIterator::pointAtX(double x) const
{
    return point2(x, yAtX(x));
}

double ProfileIterator::x() const
{
    return JEBMath::x(point());
}

double ProfileIterator::y() const
{
    return JEBMath::y(point());
}

double ProfileIterator::yAtX(double x) const
{
    double y = Profile::interpolateY(*m_Profile, x);
    if (!::JEBMath::isValid(y))
        return m_UndefinedHeight;
    else
        return y;
}

LineSegmentD ProfileIterator::segment() const
{
    return JEBMath::segment(*m_Profile, *m_Index - 1);
}

}}
