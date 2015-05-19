#include "ProfileIterator.hpp"

#include <limits>
#include "../Math/Constants.hpp"
#include "LineString.hpp"
#include "Profile.hpp"

namespace JEBMath {

using namespace std;

ProfileIterator::ProfileIterator(const Profile* prof, size_t* index)
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

size_t ProfileIterator::getIndex() const
{
    return *m_Index;
}

void ProfileIterator::setIndex(size_t index)
{
    *m_Index = std::min(index, m_Profile->size());
}

const Profile* ProfileIterator::getProfile() const
{
    return m_Profile;
}

double ProfileIterator::getUndefinedHeight() const
{
    return m_UndefinedHeight;
}

void ProfileIterator::setUndefinedHeight(double undefinedHeight)
{
    m_UndefinedHeight = undefinedHeight;
}

Vector<double, 2> ProfileIterator::getPoint() const
{
    return (*m_Profile)[*m_Index];
}

Vector<double, 2> ProfileIterator::getPointAtX(double x) const
{
    return vector2(x, getYAtX(x));
}

double ProfileIterator::getX() const
{
    using JEBMath::getX;
    return getX(getPoint());
}

double ProfileIterator::getY() const
{
    using JEBMath::getY;
    return getY(getPoint());
}

double ProfileIterator::getYAtX(double x) const
{
    using JEBMath::isValid;
    double y = interpolateY(*m_Profile, x);
    if (!isValid(y))
        return m_UndefinedHeight;
    else
        return y;
}

LineSegment<double, 2> ProfileIterator::getSegment() const
{
    using JEBMath::getSegment;
    return getSegment(*m_Profile, *m_Index - 1);
}

}
