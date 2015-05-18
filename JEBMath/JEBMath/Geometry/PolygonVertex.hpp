#ifndef JEBMATH_POLYGONERTEX_HPP
#define JEBMATH_POLYGONERTEX_HPP

#include <iosfwd>
#include "Vector.hpp"

namespace JEBMath { namespace Polygon {

struct Vertex;

struct Spoke
{
    Spoke(Vertex* vertex, Vertex** other)
        : right(NULL),
          left(NULL),
          vertex(vertex),
          other(other)
    {}

    Spoke* right;
    Spoke* left;
    Vertex* vertex;
    Vertex** other;
};

inline Spoke* nextSpoke(const Spoke* hand)
{
    return hand->right;
}

inline Vertex* otherSpoke(const Spoke* hand)
{
    return *hand->other;
}

std::ostream& operator<<(std::ostream& os, const Spoke& h);

struct Vertex
{
    Vertex(double offset,
           const Vector<double, 2>& point,
           Vertex* prev = NULL,
           Vertex* next = NULL)
        : offset(offset),
          point(point),
          next(next),
          prev(prev),
          spoke(NULL)
    {
    }

    double offset;
    Vector<double, 2> point;
    Vertex* next;
    Vertex* prev;
    Spoke* spoke;
};

inline Vertex* nextVertex(Vertex* vertex)
{
    return vertex->next;
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

void createSpokes(Vertex* vertex1, Vertex* vertex2);

Spoke* findSpoke(const Vertex* vertex, const Vertex* other);

void updateSpokes(Spoke* isect, Vertex* vertex);

std::pair<Vertex*, Vertex*> getFirstEdge(Vertex* vertex);

Vertex* createVertex(double offset, const Vector<double, 2>& p);

Vertex* createVertex(Vertex* next, double offset, const Vector<double, 2>& p);

void deleteAll(Vertex* vertex);

Vertex* findInsertPos(Vertex* first, double offset, double tolerance);

Vertex* nextZeroOffsetVertex(Vertex* first);

}}

#endif
