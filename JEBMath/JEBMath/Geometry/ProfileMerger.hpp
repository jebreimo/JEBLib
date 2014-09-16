#ifndef JEB_MATH_PROFILEMERGER_HPP
#define JEB_MATH_PROFILEMERGER_HPP

#include "LineString.hpp"

namespace JEBMath { namespace Dim2 {

class ProfileIterator;

class ProfileMerger
{
public:
    typedef Point<double, 2> Point;
    typedef std::vector<Point> LineString;

    ProfileMerger();

    enum Method
    {
        SelectUpper,
        SelectLower
    };

    void setProfiles(const LineString& a, const LineString& b);

    double maxExtrapolation() const;
    void setMaxExtrapolation(double maxExtrapolation);

    double maxInterpolation() const;
    void setMaxInterpolation(double maxInterpolation);

    Method method() const;
    void setMethod(Method method);

    double precision() const;
    void setPrecision(double precision);

    const LineString& result() const;

    bool nextResult();
private:
    unsigned getStartPoint(Point& p,
                           const LineString* profA,
                           const LineString* profB) const;
    unsigned getEndPoint(Point& p,
                         const LineString* profA,
                         const LineString* profB) const;
    bool nextUpper(ProfileIterator* itLo, ProfileIterator* itHi);
    bool nextLower(ProfileIterator* itLo, ProfileIterator* itHi);
    void processTail(ProfileIterator* main, ProfileIterator* other);

    size_t m_IndexA;
    size_t m_IndexB;
    double m_MaxExtrapolation;
    double m_MaxInterpolation;
    Method m_Method;
    double m_Precision;
    LineString m_ProfileA;
    LineString m_ProfileB;
    LineString m_Result;
};

}}

#endif
