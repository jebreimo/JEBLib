#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../Math/Constants.hpp"
#include "Distance.hpp"
#include "Intersections.hpp"
#include "Profile.hpp"
#include "ProfileIterator.hpp"
#include "ProfileMerger.hpp"

namespace JEBMath {

using namespace std;

static void addPoints(Profile& prof, ProfileIterator& it);
static bool addRemainder(Profile& result,
                         const Profile& prof,
                         size_t& index,
                         const Profile& otherProf);
static void addUniquePoint(Profile& prof,
                           const Vector<double, 2>& p,
                           double precision);
static LineSegment<double, 2> extrapolate(const LineSegment<double, 2>& orig, double length);
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

void ProfileMerger::setProfiles(const Profile& a, const Profile& b)
{
    m_ProfileA.clear();
    m_ProfileB.clear();

    Vector<double, 2> p;
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

double ProfileMerger::getMaxExtrapolation() const
{
    return m_MaxExtrapolation;
}

void ProfileMerger::setMaxExtrapolation(double maxExtrapolation)
{
    assert(maxExtrapolation >= 0);
    m_MaxExtrapolation = maxExtrapolation;
}

double ProfileMerger::getMaxInterpolation() const
{
    return m_MaxInterpolation;
}

void ProfileMerger::setMaxInterpolation(double maxInterpolation)
{
    assert(maxInterpolation >= 0);
    m_MaxInterpolation = maxInterpolation;
}

ProfileMerger::Method ProfileMerger::getMethod() const
{
    return m_Method;
}

void ProfileMerger::setMethod(Method method)
{
    m_Method = method;
}

double ProfileMerger::getPrecision() const
{
    return m_Precision;
}

void ProfileMerger::setPrecision(double precision)
{
    m_Precision = precision;
}

const Profile& ProfileMerger::getResult() const
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
    if (itA.getX() > itB.getX() ||
        (itA.getX() == itB.getX() && (
            (m_Method == SelectLower && itA.getY() > itB.getY()) ||
            (m_Method == SelectUpper && itA.getY() < itB.getY()))))
        std::swap(itA, itB);

    if (m_Method == SelectUpper)
        return nextUpper(&itB, &itA);
    else
        return nextLower(&itA, &itB);
}

unsigned ProfileMerger::getStartPoint(Vector<double, 2>& p,
                                      const Profile* profA,
                                      const Profile* profB) const
{
    if (m_MaxExtrapolation == 0 || profA->size() < 2 || profB->size() < 2)
        return 0;

    auto pa = profA->front();
    auto pb = profB->front();
    if (pa == pb)
        return 0;

    unsigned flags = 0;
    if (getX(pa) < getX(pb))
    {
        flags = 0x2;
    }
    else if (getX(pa) > getX(pb))
    {
        std::swap(profA, profB);
        flags = 0x1;
    }
    if (flags)
    {
        auto ext = extrapolate(getFirstSegment(*profB), -m_MaxExtrapolation);
        if (firstIntersection(p, ext, *profA))
            return flags;
    }
    if (fabs(getX(pa) - getX(pb)) < m_MaxExtrapolation)
    {
        auto extA = extrapolate(getFirstSegment(*profA), -m_MaxExtrapolation);
        auto extB = extrapolate(getFirstSegment(*profB), -m_MaxExtrapolation);
        if (intersection(p, extA, extB, 0) == INTERSECTING)
            return 0x3;
    }

    return 0;
}

unsigned ProfileMerger::getEndPoint(Vector<double, 2>& p,
                                    const Profile* profA,
                                    const Profile* profB) const
{
    if (m_MaxExtrapolation == 0 || profA->size() < 2 || profB->size() < 2)
        return 0;

    auto pa = profA->back();
    auto pb = profB->back();
    if (pa == pb)
        return 0;

    unsigned flags = 0;
    if (getX(pa) > getX(pb))
    {
        flags = 0x2;
    }
    else if (getX(pa) < getX(pb))
    {
        std::swap(profA, profB);
        flags = 0x1;
    }
    if (flags)
    {
        auto ext = extrapolate(getLastSegment(*profB), m_MaxExtrapolation);
        if (firstIntersection(p, ext, *profA))
            return flags;
    }
    if (fabs(getX(pa) - getX(pb)) < m_MaxExtrapolation)
    {
        auto extA = extrapolate(getLastSegment(*profA), m_MaxExtrapolation);
        auto extB = extrapolate(getLastSegment(*profB), m_MaxExtrapolation);
        if (intersection(p, extA, extB, 0) == INTERSECTING)
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
                addUniquePoint(m_Result, itLo->getPoint(), m_Precision);
            it->next();
        }
        else if (itHi->getIndex() == 0)
        {
            Vector<double, 2> nearest;
            size_t index;
            if (nearestPointBefore(nearest,
                                   index,
                                   *itLo->getProfile(),
                                   itHi->getProfile()->front()) &&
                getDistance(itHi->getProfile()->front(), nearest) <= m_MaxInterpolation)
            {
                addUniquePoint(m_Result, nearest, m_Precision);
                swap(itHi, itLo);
            }
            else
            {
                addUniquePoint(m_Result, vector2(it->getX(), yLo), m_Precision);
                return true;
            }
        }
        else
        {
            Vector<double, 2> isect;
            if (intersection(isect, itLo->getSegment(), itHi->getSegment(), 0) == INTERSECTING)
            {
                addUniquePoint(m_Result, isect, m_Precision);
                if (areEquivalent(it->getPoint(), isect, m_Precision))
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
                addUniquePoint(m_Result, itHi->getPoint(), m_Precision);
            it->next();
        }
        else if (itLo->getIndex() == 0)
        {
            Vector<double, 2> nearest;
            size_t index;
            if (nearestPointBefore(nearest,
                                   index,
                                   *itHi->getProfile(),
                                   itLo->getProfile()->front()) &&
                getDistance(itLo->getProfile()->front(), nearest) <= m_MaxInterpolation)
            {
                addUniquePoint(m_Result, nearest, m_Precision);
                swap(itHi, itLo);
            }
            else
            {
                addUniquePoint(m_Result, vector2(it->getX(), yHi), m_Precision);
                return true;
            }
        }
        else
        {
            Vector<double, 2> isect;
            if (intersection(isect, itLo->getSegment(), itHi->getSegment(), 0) == INTERSECTING)
            {
                addUniquePoint(m_Result, isect, m_Precision);
                if (areEquivalent(it->getPoint(), isect, m_Precision))
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
        Vector<double, 2> nearest;
        size_t index;
        if (nearestPointAfter(nearest,
                              index,
                              *other->getProfile(),
                              m_Result.back()) &&
            getDistance(m_Result.back(), nearest) <= m_MaxInterpolation)
        {
            addUniquePoint(m_Result, nearest, m_Precision);
            other->setIndex(index + 1);
            if (other->isValid() &&
                areEquivalent(other->getPoint(), m_Result.back(), m_Precision))
                other->next();
            addPoints(m_Result, *other);
        }
    }
}

static void addPoints(Profile& prof, ProfileIterator& it)
{
    while (it.isValid())
    {
        prof.push_back(it.getPoint());
        it.next();
    }
}

static bool addRemainder(Profile& result,
                         const Profile& prof,
                         size_t& index,
                         const Profile& otherProf)
{
    if (index != 0 &&
        !otherProf.empty() &&
        getX(prof[index - 1]) < getX(otherProf.back()))
    {
        double xc = getX(otherProf.back());
        result.push_back(vector2(xc, interpolateY(prof, xc)));
    }

    result.insert(result.end(), prof.begin() + index, prof.end());
    index = prof.size();
    return result.size() >= 2;
}

static void addUniquePoint(Profile& prof,
                           const Vector<double, 2>& p,
                           double precision)
{
    if (prof.empty() || !areEquivalent(prof.back(), p, precision))
        prof.push_back(p);
}

static LineSegment<double, 2> extrapolate(const LineSegment<double, 2>& orig, double length)
{
    auto v = getUnit(orig.getVector()) * length;
    if (length >= 0)
        return makeLineSegment(orig.getEnd(), orig.getEnd() + v);
    else
        return makeLineSegment(orig.getStart(), orig.getStart() + v);
}

static ProfileIterator* getNearestIterator(ProfileIterator* itLo,
                                           ProfileIterator* itHi,
                                           double& yLo,
                                           double& yHi,
                                           ProfileMerger::Method method)
{
    if (itLo->getX() < itHi->getX())
    {
        yLo = itLo->getY();
        yHi = itHi->getYAtX(itLo->getX());
        return itLo;
    }
    else if (itLo->getX() > itHi->getX())
    {
        yLo = itLo->getYAtX(itHi->getX());
        yHi = itHi->getY();
        return itHi;
    }
    else
    {
        yLo = itLo->getY();
        yHi = itHi->getY();
        if ((method == ProfileMerger::SelectLower && yLo > yHi) ||
            (method == ProfileMerger::SelectUpper && yLo <= yHi))
            return itLo;
        else
            return itHi;
    }
}

}
