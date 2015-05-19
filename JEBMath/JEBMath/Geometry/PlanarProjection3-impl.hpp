namespace JEBMath {

template <typename T>
PlanarProjection3<T>::PlanarProjection3(const Plane3<T>& plane)
{
    plane.getUnitVectors(m_Unit1, m_Unit2);
    m_Offsets[0] = m_Unit1 * plane.getOrigin();
    m_Offsets[1] = m_Unit2 * plane.getOrigin();
}

template <typename T>
Vector<T, 2> PlanarProjection3<T>::operator()(const Vector<T, 3>& point)
{
    return vector2(m_Unit1 * point - m_Offsets[0],
                   m_Unit2 * point - m_Offsets[1]);
}

template <typename T>
PlanarProjection3<T> makePlanarProjection(const Plane3<T>& plane)
{
    return PlanarProjection3<T>(plane);
}

}
