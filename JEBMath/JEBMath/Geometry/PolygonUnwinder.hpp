#ifndef JEB_MATH_POLYGONUNWINDER_HPP
#define JEB_MATH_POLYGONUNWINDER_HPP

#include <iosfwd>
#include <utility>
#include "JEBBase/Iterators/Iterators.hpp"
#include "PolygonVertex.hpp"
#include "Types.hpp"

namespace JEBMath { namespace Polygon {

class Unwinder
{
public:
    Unwinder();
    ~Unwinder();

    double tolerance() const;
    void setTolerance(double tolerance);

    template <typename FwdIt>
    void setPolygon(FwdIt begin, FwdIt end);

    bool isSelfIntersecting();

    void clear();
    void prepare();
    void print(std::ostream& os) const;

    std::vector<Point<double, 2>> hull();
    std::vector<std::vector<Point<double, 2>>> split();
private:
    /** @return the next vertex that should be checked for intersections.
     */
    Vertex* insertIntersections(Vertex* first,
                                const Dim2::LineSegmentD& line1,
                                Vertex* second);

    /** @return the next vertex that should be checked for intersections.
     */
    Vertex* insertIntersections(Vertex* lineStart,
                                const Vertex* searchEnd);

    void insertIntersections(double offset1,
                             double offset2,
                             Vertex* vertex1,
                             Vertex* vertex2,
                             const Dim2::LineSegmentD& line1,
                             const Dim2::LineSegmentD& line2);

    Vertex* vertexAtOffset(Vertex* vertex,
                           const Dim2::LineSegmentD& line,
                           double offset);

    Vertex* m_FirstVertex;
    bool m_Prepared;
    double m_Tolerance;
};

namespace detail
{
template <typename Point>
Dim2::PointD toPoint2D(const Point& p) {return Dim2::pointD(x(p), y(p));}
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
