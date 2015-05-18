namespace JEBMath {

template <typename T>
Plane3<T>::Plane3()
{}

template <typename T>
Plane3<T>::Plane3(const Vector<T, 3>& origin, const Vector<T, 3>& normal)
    : m_Origin(origin),
      m_Normal(normal)
{}

template <typename T>
bool Plane3<T>::getUnitVectors(Vector<T, 3>& unit1, Vector<T, 3>& unit2) const
{
    if (getX(m_Normal) != 0 || getY(m_Normal) != 0)
        setXYZ<T>(unit1, -getY(m_Normal), getX(m_Normal), 0);
    else if (getZ(m_Normal) != 0)
        setXYZ<T>(unit1, getZ(m_Normal), 0, 0);
    else
        return false;

    unit1 = getUnit(unit1);
    unit2 = getUnit(cross(m_Normal, unit1));
    return true;
}

template <typename T>
const Vector<T, 3>& Plane3<T>::getOrgin() const
{
    return m_Origin;
}

template <typename T>
void Plane3<T>::setOrgin(const Vector<T, 3>& orgin)
{
    m_Origin = orgin;
}

template <typename T>
const Vector<T, 3>& Plane3<T>::getNormal() const
{
    return m_Normal;
}

template <typename T>
void Plane3<T>::setNormal(const Vector<T, 3>& normal)
{
    m_Normal = normal;
}

}
