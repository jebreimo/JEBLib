namespace JEBMath {

template <unsigned N>
CubicHermiteSpline<N>::CubicHermiteSpline()
{
}

template <unsigned N>
CubicHermiteSpline<N>::CubicHermiteSpline(
        const Vector<double, N>& start,
        const Vector<double, N>& startTangent,
        const Vector<double, N>& end,
        const Vector<double, N>& endTangent)
{
    setPointsAndTangents(start, startTangent, end, endTangent);
}

template <unsigned N>
const Vector<double, N>& CubicHermiteSpline<N>::getStart() const
{
    return m_Start;
}

template <unsigned N>
const Vector<double, N>& CubicHermiteSpline<N>::getStartTangent() const
{
    return m_StartTangent;
}

template <unsigned N>
Vector<double, N> CubicHermiteSpline<N>::getEnd() const
{
    return m_Start + m_A + m_B + m_StartTangent;
}

template <unsigned N>
Vector<double, N> CubicHermiteSpline<N>::getEndTangent() const
{
    return m_StartTangent + 3 * m_A + 2 * m_B;
}

template <unsigned N>
void CubicHermiteSpline<N>::setPointsAndTangents(
        const Vector<double, N>& start,
        const Vector<double, N>& startTangent,
        const Vector<double, N>& end,
        const Vector<double, N>& endTangent)
{
    m_Start = start;
    m_StartTangent = startTangent;
    auto s = end - start;
    m_A = startTangent + endTangent - 2 * s;
    m_B = 3 * s - 2 * startTangent - endTangent;
}

template <unsigned N>
Vector<double, N> CubicHermiteSpline<N>::getPointAt(double t) const
{
    // The following computation is a slightly optimized rearrangement of the
    // Hermite formula; it gives the exact same result, but by re-arranging
    // the factors it uses 3 instead of 4 multiplications.
    return m_Start + (m_StartTangent + (m_B + m_A * t) * t) * t;
}

}
