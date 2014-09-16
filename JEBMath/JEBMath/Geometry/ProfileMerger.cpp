#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "JEBMath/Math/Constants.hpp"
#include "Distance.hpp"
#include "Intersections.hpp"
#include "Profile.hpp"
#include "ProfileIterator.hpp"
#include "ProfileMerger.hpp"

namespace JEBMath { namespace Dim2 {

using namespace std;

static void addPoints(LineStringD& prof, ProfileIterator& it);
static bool addRemainder(LineStringD& result,
                         const LineStringD& prof,
                         size_t& index,
                         const LineStringD& otherProf);
static void addUniquePoint(LineStringD& prof,
                           const PointD& p,
                           double precision);
static LineSegmentD extrapolate(const LineSegmentD& orig, double length);
static ProfileIterator* getNearestIterator(ProfileIterator* itLo,
                                           ProfileIterator* itHi,
                                           double& yLo,
                                           double& yHi,
                                           ProfileMerger::Method method);

ProfileMerger::ProfileMerger()
    : m_IndexA(0),
      m_IndexB(0),
      m_MaxExtrapolation(0),
      m_MaxInterpolation(0),
      m_Method(SelectLower),
      m_Precision(1e-9)
{
}

void ProfileMerger::setProfiles(const LineString& a, const LineString& b)
{
    m_ProfileA.clear();
    m_ProfileB.clear();

    Point p;
    unsigned flags;

    flags = getStartPoint(p, &a, &b);
    if (flags & 0x1)
        m_ProfileA.push_back(p);
    if (flags & 0x2)
        m_ProfileB.push_back(p);

    m_ProfileA.insert(m_ProfileA.end(), a.begin(), a.end());
    m_ProfileB.insert(m_ProfileB.end(), b.begin(), b.end());

    flags = getEndPoint(p, &a, &b);
    if (flags & 0x1)
        m_ProfileA.push_back(p);
    if (flags & 0x2)
        m_ProfileB.push_back(p);

    m_IndexA = m_IndexB = 0;
}

double ProfileMerger::maxExtrapolation() const
{
    return m_MaxExtrapolation;
}

void ProfileMerger::setMaxExtrapolation(double maxExtrapolation)
{
    assert(maxExtrapolation >= 0);
    m_MaxExtrapolation = maxExtrapolation;
}

double ProfileMerger::maxInterpolation() const
{
    return m_MaxInterpolation;
}

void ProfileMerger::setMaxInterpolation(double maxInterpolation)
{
    assert(maxInterpolation >= 0);
    m_MaxInterpolation = maxInterpolation;
}

ProfileMerger::Method ProfileMerger::method() const
{
    return m_Method;
}

void ProfileMerger::setMethod(Method method)
{
    m_Method = method;
}

double ProfileMerger::precision() const
{
    return m_Precision;
}

void ProfileMerger::setPrecision(double precision)
{
    m_Precision = precision;
}

const ProfileMerger::LineString& ProfileMerger::result() const
{
    return m_Result;
}

bool ProfileMerger::nextResult()
{
    m_Result.clear();
    if (m_IndexA == m_ProfileA.size())
        return addRemainder(m_Result, m_ProfileB, m_IndexB, m_ProfileA);
    else if (m_IndexB == m_ProfileB.size())
        return addRemainder(m_Result, m_ProfileA, m_IndexA, m_ProfileB);

    ProfileIterator itA(&m_ProfileA, &m_IndexA);
    ProfileIterator itB(&m_ProfileB, &m_IndexB);
    if (itA.x() > itB.x() ||
        (itA.x() == itB.x() && (
            (m_Method == SelectLower && itA.y() > itB.y()) ||
            (m_Method == SelectUpper && itA.y() < itB.y()))))
        std::swap(itA, itB);

    if (m_Method == SelectUpper)
        return nextUpper(&itB, &itA);
    else
        return nextLower(&itA, &itB);
}

unsigned ProfileMerger::getStartPoint(Point& p,
                                      const LineString* profA,
                                      const LineString* profB) const
{
    if (m_MaxExtrapolation == 0 || profA->size() < 2 || profB->size() < 2)
        return 0;

    PointD pa = profA->front();
    PointD pb = profB->front();
    if (pa == pb)
        return 0;

    unsigned flags = 0;
    if (x(pa) < x(pb))
    {
        flags = 0x2;
    }
    else if (x(pa) > x(pb))
    {
        std::swap(profA, profB);
        flags = 0x1;
    }
    if (flags)
    {
        LineSegmentD ext = extrapolate(firstSegment(*profB), -m_MaxExtrapolation);
        if (Profile::firstIntersection(p, ext, *profA))
            return flags;
    }
    if (fabs(x(pa) - x(pb)) < m_MaxExtrapolation)
    {
        LineSegmentD extA = extrapolate(firstSegment(*profA), -m_MaxExtrapolation);
        LineSegmentD extB = extrapolate(firstSegment(*profB), -m_MaxExtrapolation);
        if (intersection(p, extA, extB, 0) == Intersecting)
            return 0x3;
    }

    return 0;
}

unsigned ProfileMerger::getEndPoint(Point& p,
                                    const LineString* profA,
                                    const LineString* profB) const
{
    if (m_MaxExtrapolation == 0 || profA->size() < 2 || profB->size() < 2)
        return 0;

    PointD pa = profA->back();
    PointD pb = profB->back();
    if (pa == pb)
        return 0;

    unsigned flags = 0;
    if (x(pa) > x(pb))
    {
        flags = 0x2;
    }
    else if (x(pa) < x(pb))
    {
        std::swap(profA, profB);
        flags = 0x1;
    }
    if (flags)
    {
        LineSegmentD ext = extrapolate(lastSegment(*profB), m_MaxExtrapolation);
        if (Profile::firstIntersection(p, ext, *profA))
            return flags;
    }
    if (fabs(x(pa) - x(pb)) < m_MaxExtrapolation)
    {
        LineSegmentD extA = extrapolate(lastSegment(*profA), m_MaxExtrapolation);
        LineSegmentD extB = extrapolate(lastSegment(*profB), m_MaxExtrapolation);
        if (intersection(p, extA, extB, 0) == Intersecting)
            return 0x3;
    }

    return 0;
}

bool ProfileMerger::nextLower(ProfileIterator* itLo, ProfileIterator* itHi)
{
    while (itHi->isValid() && itLo->isValid())
    {
        double yHi, yLo;
        ProfileIterator* it = getNearestIterator(itLo, itHi, yLo, yHi, m_Method);

        if (yLo <= yHi)
        {
            if (it == itLo)
                addUniquePoint(m_Result, itLo->point(), m_Precision);
            it->next();
        }
        else if (itHi->index() == 0)
        {
            Point nearest;
            size_t index;
            if (Profile::nearestPointBefore(nearest,
                                            index,
                                            *itLo->profile(),
                                            itHi->profile()->front()) &&
                distance(itHi->profile()->front(), nearest) <= m_MaxInterpolation)
            {
                addUniquePoint(m_Result, nearest, m_Precision);
                swap(itHi, itLo);
            }
            else
            {
                addUniquePoint(m_Result, point2(it->x(), yLo), m_Precision);
                return true;
            }
        }
        else
        {
            Point isect;
            if (intersection(isect, itLo->segment(), itHi->segment(), 0) == Intersecting)
            {
                addUniquePoint(m_Result, isect, m_Precision);
                if (equivalent(it->point(), isect, m_Precision))
                    it->next();
            }
            else
            {
                itLo->next();
            }
            swap(itHi, itLo);
        }
    }

    processTail(itLo, itHi);

    return m_Result.size() >= 2;
}

bool ProfileMerger::nextUpper(ProfileIterator* itLo, ProfileIterator* itHi)
{
    while (itHi->isValid() && itLo->isValid())
    {
        double yHi, yLo;
        ProfileIterator* it = getNearestIterator(itLo, itHi, yLo, yHi, m_Method);

        if (yLo < yHi)
        {
            if (it == itHi)
                addUniquePoint(m_Result, itHi->point(), m_Precision);
            it->next();
        }
        else if (itLo->index() == 0)
        {
            Point nearest;
            size_t index;
            if (Profile::nearestPointBefore(nearest,
                                            index,
                                            *itHi->profile(),
                                            itLo->profile()->front()) &&
                distance(itLo->profile()->front(), nearest) <= m_MaxInterpolation)
            {
                addUniquePoint(m_Result, nearest, m_Precision);
                swap(itHi, itLo);
            }
            else
            {
                addUniquePoint(m_Result, point2(it->x(), yHi), m_Precision);
                return true;
            }
        }
        else
        {
            Point isect;
            if (intersection(isect, itLo->segment(), itHi->segment(), 0) == Intersecting)
            {
                addUniquePoint(m_Result, isect, m_Precision);
                if (equivalent(it->point(), isect, m_Precision))
                    it->next();
            }
            else
            {
                itHi->next();
            }
            swap(itHi, itLo);
        }
    }

    processTail(itHi, itLo);

    return m_Result.size() >= 2;
}

void ProfileMerger::processTail(ProfileIterator* main, ProfileIterator* other)
{
    if (main->isValid())
    {
      addPoints(m_Result, *main);
    }
    else
    {
        Point nearest;
        size_t index;
        if (Profile::nearestPointAfter(nearest,
                                       index,
                                       *other->profile(),
                                       m_Result.back()) &&
            distance(m_Result.back(), nearest) <= m_MaxInterpolation)
        {
            addUniquePoint(m_Result, nearest, m_Precision);
            other->setIndex(index + 1);
            if (other->isValid() &&
                equivalent(other->point(), m_Result.back(), m_Precision))
                other->next();
            addPoints(m_Result, *other);
        }
    }
}

static void addPoints(LineStringD& prof, ProfileIterator& it)
{
    while (it.isValid())
    {
        prof.push_back(it.point());
        it.next();
    }
}

static bool addRemainder(LineStringD& result,
                         const LineStringD& prof,
                         size_t& index,
                         const LineStringD& otherProf)
{
    if (index != 0 &&
        !otherProf.empty() &&
        x(prof[index - 1]) < x(otherProf.back()))
    {
        double xc = x(otherProf.back());
        result.push_back(point2(xc, Profile::interpolateY(prof, xc)));
    }

    result.insert(result.end(), prof.begin() + index, prof.end());
    index = prof.size();
    return result.size() >= 2;
}

static void addUniquePoint(LineStringD& prof,
                           const PointD& p,
                           double precision)
{
    if (prof.empty() || !equivalent(prof.back(), p, precision))
        prof.push_back(p);
}

static LineSegmentD extrapolate(const LineSegmentD& orig, double length)
{
    VectorD v = unit(orig.vector()) * length;
    if (length >= 0)
        return LineSegmentD(orig.end(), translate(orig.end(), v));
    else
        return LineSegmentD(orig.start(), translate(orig.start(), v));
}

static ProfileIterator* getNearestIterator(ProfileIterator* itLo,
                                           ProfileIterator* itHi,
                                           double& yLo,
                                           double& yHi,
                                           ProfileMerger::Method method)
{
    if (itLo->x() < itHi->x())
    {
        yLo = itLo->y();
        yHi = itHi->yAtX(itLo->x());
        return itLo;
    }
    else if (itLo->x() > itHi->x())
    {
        yLo = itLo->yAtX(itHi->x());
        yHi = itHi->y();
        return itHi;
    }
    else
    {
        yLo = itLo->y();
        yHi = itHi->y();
        if ((method == ProfileMerger::SelectLower && yLo > yHi) ||
            (method == ProfileMerger::SelectUpper && yLo <= yHi))
            return itLo;
        else
            return itHi;
    }
}

}}
