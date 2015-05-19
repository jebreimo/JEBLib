#include "Profile.hpp"

#include <cassert>
#include <limits>
#include "../Math/Constants.hpp"
#include "Distance.hpp"
#include "Intersections.hpp"

namespace JEBMath {

using namespace std;

namespace
{
    int compare(double a, double b)
    {
        if (a < b)
            return -1;
        else
            return a > b;
    }

    double getTAtX(const LineSegment<double, 2>& l, double xc)
    {
        return (xc - getX(l.getStart())) / getX(l.getVector());
    }

    double getYAtX(const LineSegment<double, 2>& l, double xc)
    {
        return getY(l.getStart()) + getTAtX(l, xc) * getY(l.getVector());
    }

    bool firstIntersectionOnVertLineSegment(Vector<double, 2>& isect,
                                            const LineSegment<double, 2>& line,
                                            const Profile& prof)
    {
        double lMin = std::min(getY(line.getStart()), getY(line.getEnd()));
        double lMax = std::max(getY(line.getStart()), getY(line.getEnd()));
        double pMin = interpolateY(prof, getX(line.getStart()), PickLowest);
        double pMax = interpolateY(prof, getX(line.getStart()), PickHighest);
        if (getY(line.getVector()) >= 0)
        {
            if (pMin <= lMin && lMin <= pMax)
            {
                isect = line.getStart();
                return true;
            }
            else if (lMin <= pMin && pMin <= lMax)
            {
                isect = vector2(getX(line.getStart()), pMin);
                return true;
            }
        }
        else
        {
            if (pMin <= lMax && lMax <= pMax)
            {
                isect = line.getStart();
                return true;
            }
            else if (lMin <= pMax && pMax <= lMax)
            {
                isect = vector2(getX(line.getStart()), pMax);
                return true;
            }
        }
        return false;
    }
}

bool isProfile(const Profile& prof)
{
    if (getSegmentCount(prof) == 0)
        return false;
    for (size_t i = 1; i < prof.size(); ++i)
    {
        if (getX(prof[i - 1]) > getX(prof[i]))
            return false;
        int direction = 0;
        while (getX(prof[i - 1]) == getX(prof[i]))
        {
            int curDirection = compare(getY(prof[i - 1]), getY(prof[i]));
            if (direction == 0)
                direction = curDirection;
            else if (curDirection != 0 && curDirection != direction)
                return false;
            i++;
        }
    }

    return true;
}

size_t indexOfBottomPoint(const Profile& prof)
{
    size_t index = ::JEBMath::InvalidIndex;
    double bottom = -std::numeric_limits<double>::max();
    for (size_t i = 0; i < prof.size(); i++)
    {
        if (getY(prof[i]) < bottom)
        {
            index = i;
            bottom = getY(prof[i]);
        }
    }
    return index;
}

double interpolateY(const Profile& prof,
                    double xc,
                    ConflictResolution pick)
{
    auto i = firstSegmentAt(prof, xc);
    if (i == ::JEBMath::InvalidIndex || i == getSegmentCount(prof))
        return ::JEBMath::InvalidDouble;
    else if (xc != getX(prof[i + 1]))
        return getYAtX(getSegment(prof, i), xc);

    // If x equals the end of a line segment, it is necessary to check
    // the next segment to see if it's vertical or not. If it is, use the
    // conflict resolution method to pick the elevation.
    if (getX(prof[i]) != xc)
      i++;
    auto min = getY(prof[i]), max = getY(prof[i]);
    while (i < prof.size() && getX(prof[i]) == getX(prof[i + 1]))
    {
        i++;
        if (getY(prof[i]) < min)
            min = getY(prof[i]);
        else if (max < getX(prof[i]))
            max = getY(prof[i]);
    }
    if (pick == PickHighest)
        return max;
    else if (pick == PickMiddle)
        return (min + max) / 2;
    else
        return min;
}

size_t findProfileSegment(const Profile& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        auto mid = (min + max) / 2;
        if (getX(prof[mid]) > xc)
            max = mid - 1;
        else
            min = mid;
    }
    return min;
}

struct LineStringPos
{
    LineStringPos() : segment(0), t(0) {}
    LineStringPos(size_t segment, double t) : segment(segment), t(t) {}
    size_t segment;
    double t;
};

struct IntersectionPos
{
    LineStringPos a;
    LineStringPos b;
};

size_t lowerBound(const Profile& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        size_t mid = (min + max) / 2;
        if (getX(prof[mid]) < xc)
            min = mid + 1;
        else
            max = mid;
    }
    return min;
}

size_t upperBound(const Profile& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        size_t mid = (min + max) / 2;
        if (xc < getX(prof[mid]))
            max = mid;
        else
            min = mid + 1;
    }
    return min;
}

size_t firstSegmentAt(const Profile& prof, double xc)
{
    auto n = lowerBound(prof, xc);
    if (n > 0)
        return n - 1;
    else if (getX(prof[0]) == xc)
        return 0;
    else
        return ::JEBMath::InvalidIndex;
}

size_t lastSegmentAt(const Profile& prof, double xc)
{
    auto n = upperBound(prof, xc);
    if (n == 0)
        return ::JEBMath::InvalidIndex;
    else if (n < prof.size())
        return n - 1;
    else if (getX(prof.back()) == xc)
        return n - 2;
    else
        return n - 1;
}

bool nearestPointBefore(Vector<double, 2>& nearestPoint,
                        size_t& segmentIndex,
                        const Profile& prof,
                        const Vector<double, 2>& point)
{
    auto i = lastSegmentAt(prof, getX(point));
    auto minDist = numeric_limits<double>::max();
    if (i < getSegmentCount(prof) && getX(prof[i + 1]) > getX(point))
    {
        auto yt = getYAtX(getSegment(prof, i), getX(point));
        auto dy = getY(getSegment(prof, i).getVector());
        if ((yt <= getY(point) && dy >= 0) || (yt >= getY(point) && dy <= 0))
        {
            minDist = fabs(yt - getY(point));
            nearestPoint = vector2(getX(point), yt);
            segmentIndex = i;
            i--;
        }
    }
    else if (i == getSegmentCount(prof))
    {
        i--;
    }
    while (::JEBMath::isValid(i) && getX(point) - getX(prof[i + 1]) < minDist)
    {
        auto candidate = getNearestPoint(getSegment(prof, i), point);
        auto dist = getDistance(candidate, point);
        if (dist < minDist)
        {
            nearestPoint = candidate;
            segmentIndex = i;
            minDist = dist;
        }
        i--;
    }
    return minDist != numeric_limits<double>::max();
}


bool nearestPointAfter(Vector<double, 2>& nearestPoint,
                       size_t& segmentIndex,
                       const Profile& prof,
                       const Vector<double, 2>& point)
{
    auto i = firstSegmentAt(prof, getX(point));
    auto minDist = numeric_limits<double>::max();
    if (i < getSegmentCount(prof) && getX(prof[i]) < getX(point))
    {
        auto yt = getYAtX(getSegment(prof, i), getX(point));
        auto dy = getY(getSegment(prof, i).getVector());
        if ((yt <= getY(point) && dy <= 0) || (yt >= getY(point) && dy >= 0))
        {
            minDist = fabs(yt - getY(point));
            nearestPoint = vector2(getX(point), yt);
            segmentIndex = i;
            i++;
        }
    }
    else if (!isValid(i))
    {
        i = 0;
    }

    while (i < getSegmentCount(prof) && getX(prof[i]) - getX(point) < minDist)
    {
        auto candidate = getNearestPoint(getSegment(prof, i), point);
        auto dist = getDistance(candidate, point);
        if (dist < minDist)
        {
            nearestPoint = candidate;
            segmentIndex = i;
            minDist = dist;
        }
        i++;
    }
    return minDist != numeric_limits<double>::max();
}

bool firstIntersection(Vector<double, 2>& isect,
                       const LineSegment<double, 2>& line,
                       const Profile& prof)
{
    auto v = line.getVector();
    if (getX(v) == 0)
        return firstIntersectionOnVertLineSegment(isect, line, prof);

    auto xMin = std::min(getX(line.getStart()), getX(line.getEnd()));
    auto xMax = std::max(getX(line.getStart()), getX(line.getEnd()));
    auto iMin = firstSegmentAt(prof, xMin);
    auto iMax = lastSegmentAt(prof, xMax);
    if (iMax == ::JEBMath::InvalidIndex || iMin == getSegmentCount(prof))
        return false;
    if (iMax == getSegmentCount(prof))
        iMax = getSegmentCount(prof) - 1;
    if (iMin == ::JEBMath::InvalidIndex)
        iMin = 0;
    if (getX(v) < 0)
    {
        for (auto i = iMax; i != ::JEBMath::InvalidIndex; i--)
        {
            if (intersection(isect, getSegment(prof, i), line, 0) == INTERSECTING)
                return true;
        }
    }
    else
    {
        for (auto i = iMin; i <= iMax; i++)
        {
            if (intersection(isect, getSegment(prof, i), line, 0) == INTERSECTING)
                return true;
        }
    }

    return false;
}

}

