#ifndef JEBMATH_GEOMETRY_PROFILEITERATOR_HPP
#define JEBMATH_GEOMETRY_PROFILEITERATOR_HPP

#include <vector>
#include "LineSegment.hpp"

namespace JEBMath {

typedef std::vector<Vector<double, 2>> Profile;

class ProfileIterator
{
public:
    ProfileIterator(const Profile* prof, size_t* index);
    bool isValid() const;
    void next();

    size_t getIndex() const;
    void setIndex(size_t index);

    const Profile* getProfile() const;

    double getUndefinedHeight() const;
    void setUndefinedHeight(double undefinedHeight);

    Vector<double, 2> getPoint() const;
    Vector<double, 2> getPointAtX(double x) const;
    double getX() const;
    double getY() const;
    double getYAtX(double x) const;
    LineSegment<double, 2> getSegment() const;
private:
    const Profile* m_Profile;
    size_t* m_Index;
    double m_UndefinedHeight;
};

}

#endif
