#include "Profile.hpp"

#include <cassert>
#include <limits>
#include "JEBMath/Math/Constants.hpp"
#include "Distance.hpp"
#include "Intersections.hpp"

namespace JEBMath { namespace Dim2 {

namespace Profile
{

using namespace std;

static int compare(double a, double b)
{
    if (a < b)
        return -1;
    else
        return a > b;
}

bool isProfile(const LineStringD& prof)
{
    if (segmentCount(prof) == 0)
        return false;
    for (size_t i = 1; i < prof.size(); ++i)
    {
        if (x(prof[i - 1]) > x(prof[i]))
            return false;
        int direction = 0;
        while (x(prof[i - 1]) == x(prof[i]))
        {
            int curDirection = compare(y(prof[i - 1]), y(prof[i]));
            if (direction == 0)
                direction = curDirection;
            else if (curDirection != 0 && curDirection != direction)
                return false;
            i++;
        }
    }

    return true;
}

size_t indexOfBottomPoint(const LineStringD& prof)
{
    size_t index = ::JEBMath::InvalidIndex;
    double bottom = -std::numeric_limits<double>::max();
    for (size_t i = 0; i < prof.size(); i++)
    {
        if (y(prof[i]) < bottom)
        {
            index = i;
            bottom = y(prof[i]);
        }
    }
    return index;
}

static double tAtX(const LineSegmentD& l, double xc)
{
    return (xc - x(l.start())) / x(l.vector());
}

static double yAtX(const LineSegmentD& l, double xc)
{
    return y(l.start()) + tAtX(l, xc) * y(l.vector());
}

double interpolateY(const LineStringD& prof,
                    double xc,
                    ConflictResolution pick)
{
    size_t i = firstSegmentAt(prof, xc);
    if (i == ::JEBMath::InvalidIndex || i == segmentCount(prof))
        return ::JEBMath::InvalidDouble;
    else if (xc != x(prof[i + 1]))
        return yAtX(segment(prof, i), xc);

    // If x equals the end of a line segment, it is necessary to check
    // the next segment to see if it's vertical or not. If it is, use the
    // conflict resolution method to pick the elevation.
    if (x(prof[i]) != xc)
      i++;
    double min = y(prof[i]), max = y(prof[i]);
    while (i < prof.size() && x(prof[i]) == x(prof[i + 1]))
    {
        i++;
        if (y(prof[i]) < min)
            min = y(prof[i]);
        else if (max < x(prof[i]))
            max = y(prof[i]);
    }
    if (pick == PickHighest)
        return max;
    else if (pick == PickMiddle)
        return (min + max) / 2;
    else
        return min;
}

size_t findProfileSegment(const LineStringD& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        size_t mid = (min + max) / 2;
        if (x(prof[mid]) > xc)
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

size_t lowerBound(const LineStringD& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        size_t mid = (min + max) / 2;
        if (x(prof[mid]) < xc)
            min = mid + 1;
        else
            max = mid;
    }
    return min;
}

size_t upperBound(const LineStringD& prof, double xc)
{
    size_t min = 0, max = prof.size();
    while (min < max)
    {
        size_t mid = (min + max) / 2;
        if (xc < x(prof[mid]))
            max = mid;
        else
            min = mid + 1;
    }
    return min;
}

size_t firstSegmentAt(const LineStringD& prof, double xc)
{
    size_t n = lowerBound(prof, xc);
    if (n > 0)
        return n - 1;
    else if (x(prof[0]) == xc)
        return 0;
    else
        return ::JEBMath::InvalidIndex;
}

size_t lastSegmentAt(const LineStringD& prof, double xc)
{
    size_t n = upperBound(prof, xc);
    if (n == 0)
        return ::JEBMath::InvalidIndex;
    else if (n < prof.size())
        return n - 1;
    else if (x(prof.back()) == xc)
        return n - 2;
    else
        return n - 1;
}

bool nearestPointBefore(PointD& nearestPoint,
                        size_t& segmentIndex,
                        const LineStringD& prof,
                        const PointD& point)
{
    size_t i = lastSegmentAt(prof, x(point));
    double minDist = numeric_limits<double>::max();
    if (i < segmentCount(prof) && x(prof[i + 1]) > x(point))
    {
        double yt = yAtX(segment(prof, i), x(point));
        double dy = y(JEBMath::segment(prof, i).vector());
        if ((yt <= y(point) && dy >= 0) || (yt >= y(point) && dy <= 0))
        {
            minDist = fabs(yt - y(point));
            nearestPoint = point2(x(point), yt);
            segmentIndex = i;
            i--;
        }
    }
    else if (i == segmentCount(prof))
    {
        i--;
    }
    while (::JEBMath::isValid(i) && x(point) - x(prof[i + 1]) < minDist)
    {
        PointD candidate = ::JEBMath::nearestPoint(segment(prof, i), point);
        double dist = distance(candidate, point);
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


bool nearestPointAfter(PointD& nearestPoint,
                       size_t& segmentIndex,
                       const LineStringD& prof,
                       const PointD& point)
{
    size_t i = firstSegmentAt(prof, x(point));
    double minDist = numeric_limits<double>::max();
    if (i < segmentCount(prof) && x(prof[i]) < x(point))
    {
        double yt = yAtX(segment(prof, i), x(point));
        double dy = y(segment(prof, i).vector());
        if ((yt <= y(point) && dy <= 0) || (yt >= y(point) && dy >= 0))
        {
            minDist = fabs(yt - y(point));
            nearestPoint = point2(x(point), yt);
            segmentIndex = i;
            i++;
        }
    }
    else if (!isValid(i))
    {
        i = 0;
    }

    while (i < segmentCount(prof) && x(prof[i]) - x(point) < minDist)
    {
        PointD candidate = ::JEBMath::nearestPoint(segment(prof, i), point);
        double dist = distance(candidate, point);
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

static bool firstIntersectionOnVertLineSegment(PointD& isect,
                                               const LineSegmentD& line,
                                               const LineStringD& prof)
{
    double lMin = std::min(y(line.start()), y(line.end()));
    double lMax = std::max(y(line.start()), y(line.end()));
    double pMin = interpolateY(prof, x(line.start()), PickLowest);
    double pMax = interpolateY(prof, x(line.start()), PickHighest);
    if (y(line.vector()) >= 0)
    {
        if (pMin <= lMin && lMin <= pMax)
        {
            isect = line.start();
            return true;
        }
        else if (lMin <= pMin && pMin <= lMax)
        {
            isect = point2(x(line.start()), pMin);
            return true;
        }
    }
    else
    {
        if (pMin <= lMax && lMax <= pMax)
        {
            isect = line.start();
            return true;
        }
        else if (lMin <= pMax && pMax <= lMax)
        {
            isect = point2(x(line.start()), pMax);
            return true;
        }
    }
    return false;
}

bool firstIntersection(PointD& isect,
                       const LineSegmentD& line,
                       const LineStringD& prof)
{
    VectorD v = line.vector();
    if (x(v) == 0)
        return firstIntersectionOnVertLineSegment(isect, line, prof);

    double xMin = std::min(x(line.start()), x(line.end()));
    double xMax = std::max(x(line.start()), x(line.end()));
    size_t iMin = firstSegmentAt(prof, xMin);
    size_t iMax = lastSegmentAt(prof, xMax);
    if (iMax == ::JEBMath::InvalidIndex || iMin == segmentCount(prof))
        return false;
    if (iMax == segmentCount(prof))
        iMax = segmentCount(prof) - 1;
    if (iMin == ::JEBMath::InvalidIndex)
        iMin = 0;
    if (x(v) < 0)
    {
        for (size_t i = iMax; i != ::JEBMath::InvalidIndex; i--)
        {
            if (intersection(isect, segment(prof, i), line, 0) == Intersecting)
                return true;
        }
    }
    else
    {
        for (size_t i = iMin; i <= iMax; i++)
        {
            if (intersection(isect, segment(prof, i), line, 0) == Intersecting)
                return true;
        }
    }

    return false;
}

}
}}
