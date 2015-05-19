#ifndef JEBMATH_GEOMETRY_PROFILEMERGER_HPP
#define JEBMATH_GEOMETRY_PROFILEMERGER_HPP

#include <vector>
#include "Vector.hpp"

namespace JEBMath {

class ProfileIterator;
typedef std::vector<Vector<double, 2>> Profile;

class ProfileMerger
{
public:
    ProfileMerger();

    enum Method
    {
        SelectUpper,
        SelectLower
    };

    void setProfiles(const Profile& a, const Profile& b);

    double getMaxExtrapolation() const;
    void setMaxExtrapolation(double maxExtrapolation);

    double getMaxInterpolation() const;
    void setMaxInterpolation(double maxInterpolation);

    Method getMethod() const;
    void setMethod(Method method);

    double getPrecision() const;
    void setPrecision(double precision);

    const Profile& getResult() const;

    bool nextResult();
private:
    unsigned getStartPoint(Vector<double, 2>& p,
                           const Profile* profA,
                           const Profile* profB) const;
    unsigned getEndPoint(Vector<double, 2>& p,
                         const Profile* profA,
                         const Profile* profB) const;
    bool nextUpper(ProfileIterator* itLo, ProfileIterator* itHi);
    bool nextLower(ProfileIterator* itLo, ProfileIterator* itHi);
    void processTail(ProfileIterator* main, ProfileIterator* other);

    size_t m_IndexA;
    size_t m_IndexB;
    double m_MaxExtrapolation;
    double m_MaxInterpolation;
    Method m_Method;
    double m_Precision;
    Profile m_ProfileA;
    Profile m_ProfileB;
    Profile m_Result;
};

}

#endif
