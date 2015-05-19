#ifndef JEBMATH_GEOMETRY_POLYGONUNWINDER_HPP
#define JEBMATH_GEOMETRY_POLYGONUNWINDER_HPP

#include <iosfwd>
#include <vector>
#include "JEBBase/Iterators/Iterators.hpp"
#include "LineSegment.hpp"
#include "PolygonVertex.hpp"

namespace JEBMath { namespace Polygon {

class Unwinder
{
public:
    Unwinder();
    ~Unwinder();

    double getTolerance() const;
    void setTolerance(double tolerance);

    template <typename FwdIt>
    void setPolygon(FwdIt begin, FwdIt end);

    bool isSelfIntersecting();

    void clear();
    void prepare();
    void print(std::ostream& os) const;

    std::vector<Vector<double, 2>> getHull();
    std::vector<std::vector<Vector<double, 2>>> split();
private:
    /** @return the next vertex that should be checked for intersections.
     */
    Vertex* insertIntersections(Vertex* first,
                                const LineSegment<double, 2>& line1,
                                Vertex* second);

    /** @return the next vertex that should be checked for intersections.
     */
    Vertex* insertIntersections(Vertex* lineStart,
                                const Vertex* searchEnd);

    void insertIntersections(double offset1,
                             double offset2,
                             Vertex* vertex1,
                             Vertex* vertex2,
                             const LineSegment<double, 2>& line1,
                             const LineSegment<double, 2>& line2);

    Vertex* getVertexAtOffset(Vertex* vertex,
                              const LineSegment<double, 2>& line,
                              double offset);

    Vertex* m_FirstVertex;
    bool m_Prepared;
    double m_Tolerance;
};

namespace detail
{
    template <typename Point>
    Vector<double, 2> toPoint2D(const Point& p)
    {
        return vector2<double>(getX(p), getY(p));
    }
}

template <typename FwdIt>
void Unwinder::setPolygon(FwdIt begin, FwdIt end)
{
    clear();
    end = JEBBase::Iterators::nth(begin, end, -1);
    if (begin == end)
        return;

    int offset = 0;
    m_FirstVertex = createVertex(offset, detail::toPoint2D(*begin));
    for (++begin; begin != end; ++begin)
        createVertex(m_FirstVertex, ++offset, detail::toPoint2D(*begin));
    m_Prepared = offset <= 3;
}

}}

#endif
