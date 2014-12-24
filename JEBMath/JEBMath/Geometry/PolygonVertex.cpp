#include "PolygonVertex.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include "JEBBase/Iterators/CircularListIterator.hpp"
#include "JEBMath/Math/Comparisons.hpp"
#include "Intersections.hpp"
#include "Polygon.hpp"
#include "SortPoints.hpp"

namespace JEBMath { namespace Polygon {

using JEBBase::Iterators::makeIterator;

std::ostream& operator<<(std::ostream& os, const Spoke& h)
{
    return os << "[" << *h.vertex << " " << **h.other
              << " | [left | " << h.left << " | right " << h.right << "]]";
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
    os << "[" << vertex.offset << " " << vertex.point;
    if (vertex.spoke)
    {
        auto it = makeIterator(vertex.spoke, nextSpoke);
        it.next();
        os << " [spokes | " << otherSpoke(*it)->offset;
        while (it.next())
            os << " " << otherSpoke(*it)->offset;
        os << "]";
    }
    os << "]";
    return os;
}

void createSpokes(Vertex* vertex1, Vertex* vertex2)
{
    Spoke* spoke[] = {
        new Spoke(vertex1, &vertex1->prev),
        new Spoke(vertex2, &vertex2->prev),
        new Spoke(vertex1, &vertex1->next),
        new Spoke(vertex2, &vertex2->next),
    };
    Dim2::sortClockwise(std::begin(spoke), std::end(spoke), vertex1->point,
                        [](const Spoke* i){return otherSpoke(i)->point;});
    spoke[0]->left = spoke[3];
    for (size_t i = 1; i < 4; i++)
    {
        spoke[i - 1]->right = spoke[i];
        spoke[i]->left = spoke[i - 1];
    }
    spoke[3]->right = spoke[0];
    vertex1->spoke = vertex2->spoke = spoke[0];
}

Spoke* findSpoke(const Vertex* vertex, const Vertex* other)
{
    assert(vertex && vertex->spoke && other);
    auto it = makeIterator(vertex->spoke, nextSpoke);
    while (it.next())
    {
        if ((*it)->vertex == vertex && *(*it)->other == other)
            return (*it);
    }
    return NULL;
}

Spoke* getRightSpoke(Spoke* spoke)
{
    if (!spoke)
        return NULL;

    auto firstIt = makeIterator(spoke, nextSpoke);
    while (firstIt.next())
    {
        Spoke* iCur = otherSpoke(*firstIt)->spoke;
        if (!iCur)
            break;
        Spoke* iLeft = otherSpoke((*firstIt)->left)->spoke;
        if (iCur != iLeft)
            break;
    }

    Spoke* result = NULL;
    auto it = makeIterator(*firstIt ? *firstIt : spoke, nextSpoke);
    double bestRatio = 0;
    Vector<double, 2> bestVec;
    if (it.next())
    {
        result = *it;
        auto vec = otherSpoke(*it)->point - spoke->vertex->point;
        bestRatio = x(vec) != 0 ? y(vec) / x(vec)
                                : std::numeric_limits<double>::max();
    }
    while (it.next())
    {
        if (!otherSpoke(result)->spoke ||
            otherSpoke(*it)->spoke != otherSpoke(result)->spoke)
        {
            auto vec = otherSpoke(*it)->point - spoke->vertex->point;
            double ratio = x(vec) != 0 ? y(vec) / x(vec)
                                       : std::numeric_limits<double>::max();
            if (ratio < bestRatio)
            {
                result = *it;
                bestRatio = ratio;
            }
        }
    }
    return result;
}

std::pair<Vertex*, Vertex*> getRightEdge(Vertex* vertex)
{
    if (vertex->spoke)
    {
        Spoke* spoke = getRightSpoke(vertex->spoke);
        return std::make_pair(spoke->vertex, otherSpoke(spoke));
    }

    if (direction(vertex->prev->point, vertex->point, vertex->next->point,
                  1e-9) & (Left | Ahead))
    {
        return std::make_pair(vertex, vertex->next);
    }
    else
    {
        return std::make_pair(vertex, vertex->prev);
    }
}

Spoke* findInsertPos(Spoke* existing,
                     Spoke* newSpoke,
                     const Dim2::DirectionComparer<double>& cmp)
{
    auto it = makeIterator(existing, nextSpoke);
    while (it.next())
        if (!cmp(otherSpoke(*it)->point, otherSpoke(newSpoke)->point))
            break;
    return *it;
}

void insert(Spoke* first,
            Spoke* newSpoke,
            const Dim2::DirectionComparer<double>& cmp)
{
    Spoke* next = findInsertPos(first, newSpoke, cmp);
    newSpoke->left = next->left;
    newSpoke->right = next;
    next->left->right = newSpoke;
    next->left = newSpoke;
}

void updateSpokes(Spoke* spoke, Vertex* vertex)
{
    assert(spoke);
    assert(!vertex->spoke);
    Dim2::DirectionComparer<double> cmp(vertex->point);
    insert(spoke, new Spoke(vertex, &vertex->prev), cmp);
    insert(spoke, new Spoke(vertex, &vertex->next), cmp);
    // Note that all vertexes at the intersection will have a pointer
    // to the same spoke instance.
    vertex->spoke = spoke;
}

std::pair<Vertex*, Vertex*> getFirstEdge(Vertex* vertex)
{
    auto it = makeIterator(vertex, nextVertex);
    if (!it.next())
        return std::make_pair(vertex, vertex);
    Vertex* loLe = *it; // Lower left
    while (it.next())
    {
        Vertex* n = *it;
        if (x((*it)->point) < x(loLe->point) ||
            (x((*it)->point) == x(loLe->point) &&
             y((*it)->point) < y(loLe->point)))
        {
            loLe = n;
        }
    }
    return getRightEdge(loLe);
}

Vertex* createVertex(double offset, const Point<double, 2>& p)
{
    Vertex* vertex = new Vertex(offset, p);
    vertex->next = vertex->prev = vertex;
    return vertex;
}

Vertex* createVertex(Vertex* next, double offset, const Point<double, 2>& p)
{
    assert(next);
    next->prev->next = new Vertex(offset, p, next->prev, next);
    next->prev = next->prev->next;
    return next->prev;
}

void deleteAll(Vertex* vertex)
{
    if (vertex)
        vertex->prev->next = NULL;
    Vertex* next;
    for (Vertex* it = vertex; it; it = next)
    {
        next = it->next;
        delete it;
    }
}

Vertex* findInsertPos(Vertex* first, double offset, double tolerance)
{
    auto it = makeIterator(first, nextVertex);
    if (it.next() && !less((*it)->offset, offset, tolerance))
        return *it;
    while (it.next())
    {
        if (!less((*it)->offset, offset, tolerance) || (*it)->offset == 0)
            return *it;
    }
    return first;
}

Vertex* nextZeroOffsetVertex(Vertex* first)
{
    double offset = std::floor(first->offset + 1);
    return findInsertPos(first, offset, 0);
}

}}
