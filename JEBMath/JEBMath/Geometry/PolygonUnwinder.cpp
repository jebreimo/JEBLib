#include "PolygonUnwinder.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include "JEBBase/Containers/UniquePairSet.hpp"
#include "JEBBase/Iterators/CircularListIterator.hpp"
#include "JEBMath/Math/Comparisons.hpp"
#include "Intersections.hpp"
#include "Polygon.hpp"

namespace JEBMath { namespace Polygon {

using JEBBase::Iterators::makeIterator;

enum Flags
{
    PrevVisited = 0x1,
    NextVisited = 0x2,
    Visited = 0x4,
};

Unwinder::Unwinder()
    : m_FirstVertex(NULL),
      m_Prepared(true),
      m_Tolerance(DoubleTolerance)
{
}

Unwinder::~Unwinder()
{
    clear();
}

double Unwinder::tolerance() const
{
    return m_Tolerance;
}

void Unwinder::setTolerance(double tolerance)
{
    m_Tolerance = tolerance;
}

bool Unwinder::isSelfIntersecting()
{
    prepare();
    auto it = makeIterator(m_FirstVertex, nextVertex);
    while (it.next())
    {
        if ((*it)->spoke)
            return true;
    }
    return false;
}

void Unwinder::clear()
{
    deleteAll(m_FirstVertex);
    m_FirstVertex = NULL;
    m_Prepared = true;
}

void Unwinder::prepare()
{
    if (m_Prepared)
        return;

    // Initialize end before any intersection points have been added.
    Vertex* end = m_FirstVertex->prev->prev;

    Vertex* it = insertIntersections(m_FirstVertex, m_FirstVertex->prev);
    while (it != end)
        it = insertIntersections(it, m_FirstVertex);

    m_Prepared = true;
}

void Unwinder::print(std::ostream& os) const
{
    auto it = makeIterator(m_FirstVertex, nextVertex);
    if (it.next())
        os << **it;
    while (it.next())
        os << " -> " << **it;
    os << '\n';
}

bool isDoubleEdge(Spoke* a, Spoke* b)
{
    return otherSpoke(a)->spoke &&
           otherSpoke(a)->spoke == otherSpoke(b)->spoke;
}

std::vector<Dim2::PointD> walk(
        const Vertex* prev,
        const Vertex* vertex,
        JEBBase::UniquePairSet<Spoke*>& corners)
{
    std::vector<Dim2::PointD> result;
    result.push_back(prev->point);
    result.push_back(vertex->point);
    bool forward = prev->next == vertex;
    const Vertex* first = prev;
    const Vertex* second = vertex;
    while (true)
    {
        if (vertex->spoke)
        {
            Spoke* cur = findSpoke(vertex, prev);
            Spoke* nxt = cur->right;
            while (isDoubleEdge(cur, nxt) && nxt->right != cur)
                nxt = nxt->right;
            cur = nxt->left;
            if (corners.get(std::make_pair(cur, nxt)))
                throw std::runtime_error("Invalid polygon.");
            corners.set(std::make_pair(cur, nxt), true);
            prev = nxt->vertex;
            vertex = otherSpoke(nxt);
            forward = prev->next == vertex;
        }
        else
        {
            prev = vertex;
            vertex = forward ? vertex->next : vertex->prev;
        }
        if (prev == first && vertex == second)
            break;
        result.push_back(vertex->point);
    }
    return result;
}

JEBBase::UniquePairSet<Spoke*> getCorners(Vertex* first)
{
    JEBBase::UniquePairSetBuilder<Spoke*> builder;
    // I'm taking advantage of the fact that all vertexes at an intersection
    // point to the same spoke instance.
    std::set<Spoke*> visited;
    auto it = makeIterator(first, nextVertex);
    while (it.next())
    {
        if ((*it)->spoke &&
            visited.find((*it)->spoke) == visited.end())
        {
            visited.insert((*it)->spoke);
            auto isectIt = makeIterator((*it)->spoke, nextSpoke);
            while (isectIt.next())
            {
                Spoke* right = (*isectIt)->right;
                if (otherSpoke(right) != otherSpoke(*isectIt) &&
                    (otherSpoke(right)->spoke == NULL ||
                     otherSpoke(right)->spoke != otherSpoke(*isectIt)->spoke))
                {
                    builder.add(std::make_pair(*isectIt, right));
                }
            }
        }
    }
    return builder.build(false);
}

void printSet(std::ostream& os, const JEBBase::UniquePairSet<Spoke*>& set)
{
    for (auto it = set.begin(); it != set.end(); ++it)
    {
        os << otherSpoke(it->first.first)->offset << "->"
           << it->first.first->vertex->offset << " "
           << it->first.second->vertex->offset << "->"
           << otherSpoke(it->first.second)->offset << ": "
           << (it->second ? "true" : "false") << "\n";
    }
}

std::vector<std::vector<Dim2::PointD>> Unwinder::split()
{
    using namespace Polygon;
    prepare();
    std::vector<std::vector<Dim2::PointD>> result;
    JEBBase::UniquePairSet<Spoke*> corners = getCorners(m_FirstVertex);
    std::pair<Vertex*, Vertex*> vertexes = getFirstEdge(m_FirstVertex);
    result.push_back(walk(vertexes.first, vertexes.second, corners));
    for (auto it = corners.begin(); it != corners.end(); ++it)
    {
        if (!it->second)
        {
            Spoke* isect;
            Spoke* isect2;
            if (it->first.first->right == it->first.second)
                isect = it->first.second, isect2 = it->first.first;
            else
                isect = it->first.first, isect2 = it->first.second;
            result.push_back(walk(isect->vertex, otherSpoke(isect), corners));
        }
    }

    return result;
}

Vertex* Unwinder::vertexAtOffset(Vertex* segStart,
                                 const Dim2::LineSegmentD& line,
                                 double offset)
{
    Vertex* nextVertex = findInsertPos(segStart, segStart->offset + offset,
                                   m_Tolerance);
    if (equal(segStart->offset + offset, nextVertex->offset, m_Tolerance))
        return nextVertex;

    return createVertex(nextVertex, segStart->offset + offset,
                      line.pointAtT(offset));
}

void Unwinder::insertIntersections(double offset1,
                                   double offset2,
                                   Vertex* vertex1,
                                   Vertex* vertex2,
                                   const Dim2::LineSegmentD& line1,
                                   const Dim2::LineSegmentD& line2)
{
    Vertex* isect1 = vertexAtOffset(vertex1, line1, offset1);
    Vertex* isect2 = vertexAtOffset(vertex2, line2, offset2);
    if (!isect1->spoke && !isect2->spoke)
        createSpokes(isect1, isect2);
    else if (!isect1->spoke)
        updateSpokes(isect2->spoke, isect1);
    else if (!isect2->spoke)
        updateSpokes(isect1->spoke, isect2);
}

Vertex* Unwinder::insertIntersections(Vertex* first,
                                      const Dim2::LineSegmentD& line1,
                                      Vertex* second)
{
    Vertex* secondEnd = nextZeroOffsetVertex(second);
    Vertex* nextStart = secondEnd;
    Dim2::LineSegmentD line2(second->point, secondEnd->point);
    double offset1, offset2;
    Dim2::LineRelationship rel = Dim2::intersection(
            offset1, offset2, line1, line2, m_Tolerance);
    if (rel == Dim2::Undetermined)
    {
        std::pair<double, double> offs1, offs2;
        if (!Dim2::overlap(offs1, offs2, line1, line2, m_Tolerance))
            return nextStart;
        if (!equal(offs1.first, 1.0, m_Tolerance) &&
            !equal(offs2.first, 1.0, m_Tolerance))
        {
            insertIntersections(offs1.first, offs2.first, first, second,
                                line1, line2);
        }
        if (!equal(offs1.first, offs1.second, m_Tolerance) &&
            !equal(offs1.second, 1.0, m_Tolerance) &&
            !equal(offs2.second, 1.0, m_Tolerance))
        {
            insertIntersections(offs1.second, offs2.second, first, second,
                                line1, line2);
        }
    }
    else if (rel == Dim2::Intersecting &&
             !equal(offset1, 1.0, m_Tolerance) &&
             !equal(offset2, 1.0, m_Tolerance))
    {
        insertIntersections(offset1, offset2, first, second, line1, line2);
    }

    return nextStart;
}

Vertex* Unwinder::insertIntersections(Vertex* lineStart,
                                      const Vertex* searchEnd)
{
    Vertex* lineEnd = nextZeroOffsetVertex(lineStart);
    Dim2::LineSegmentD line1(lineStart->point, lineEnd->point);
    Vertex* it = nextZeroOffsetVertex(lineEnd);
    while (it != searchEnd)
    {
        it = insertIntersections(lineStart, line1, it);
    }
    return lineEnd;
}

std::vector<Dim2::PointD> Unwinder::hull()
{
    std::pair<Vertex*, Vertex*> vertexes = getFirstEdge(m_FirstVertex);
    JEBBase::UniquePairSet<Spoke*> corners = getCorners(m_FirstVertex);
    return walk(vertexes.first, vertexes.second, corners);
}

}}
