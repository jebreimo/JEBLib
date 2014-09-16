namespace JEBMath {

template <typename Point, typename Vector>
CubicHermiteSpline<Point, Vector>::CubicHermiteSpline()
{
}

template <typename Point, typename Vector>
CubicHermiteSpline<Point, Vector>::CubicHermiteSpline(
        const Point& start, const Vector& startTangent,
        const Point& end, const Vector& endTangent)
{
    set(start, startTangent, end, endTangent);
}

template <typename Point, typename Vector>
const Point& CubicHermiteSpline<Point, Vector>::start() const
{
    return m_Start;
}

template <typename Point, typename Vector>
const Vector& CubicHermiteSpline<Point, Vector>::startTangent() const
{
    return m_StartTangent;
}

template <typename Point, typename Vector>
Point CubicHermiteSpline<Point, Vector>::end() const
{
    return translate(m_Start, m_A + m_B + m_StartTangent);
}

template <typename Point, typename Vector>
Vector CubicHermiteSpline<Point, Vector>::endTangent() const
{
    return m_StartTangent + 3 * m_A + 2 * m_B;
}

template <typename Point, typename Vector>
void CubicHermiteSpline<Point, Vector>::set(
        const Point& start, const Vector& startTangent,
        const Point& end, const Vector& endTangent)
{
    m_Start = start;
    m_StartTangent = startTangent;
    Vector s = end - start;
    m_A = startTangent + endTangent - 2 * s;
    m_B = 3 * s - 2 * startTangent - endTangent;
}

template <typename Point, typename Vector>
Point CubicHermiteSpline<Point, Vector>::pointAt(double t) const
{
    // The following computation is a slightly optimized rearrangement of the
    // Hermite formula; it gives the exact same result, but by re-arranging
    // the factors it uses 3 instead of 4 multiplications.
    return translate(m_Start, (m_StartTangent + (m_B + m_A * t) * t) * t);
}

}
