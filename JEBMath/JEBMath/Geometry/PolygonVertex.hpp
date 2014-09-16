#ifndef JEB_MATH_POLYGON_NODE_HPP
#define JEB_MATH_POLYGON_NODE_HPP

#include <iosfwd>
#include "Types.hpp"

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

inline Spoke* next(const Spoke* hand)
{
    return hand->right;
}

inline Vertex* other(const Spoke* hand)
{
    return *hand->other;
}

std::ostream& operator<<(std::ostream& os, const Spoke& h);

struct Vertex
{
    Vertex(double offset,
           const Point<double, 2>& point,
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
    Point<double, 2> point;
    Vertex* next;
    Vertex* prev;
    Spoke* spoke;
};

inline Vertex* next(Vertex* vertex)
{
    return vertex->next;
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

void createSpokes(Vertex* vertex1, Vertex* vertex2);

Spoke* findSpoke(const Vertex* vertex, const Vertex* other);

void updateSpokes(Spoke* isect, Vertex* vertex);

std::pair<Vertex*, Vertex*> getFirstEdge(Vertex* vertex);

Vertex* createVertex(double offset, const Dim2::PointD& p);

Vertex* createVertex(Vertex* next, double offset, const Dim2::PointD& p);

void deleteAll(Vertex* vertex);

Vertex* findInsertPos(Vertex* first, double offset, double tolerance);

Vertex* nextVertex(Vertex* first);

}}

#endif
