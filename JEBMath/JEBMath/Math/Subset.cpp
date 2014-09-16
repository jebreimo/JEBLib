#include "Subset.hpp"

#include "JEBBase/Bits/Bits.hpp"

namespace JEBMath {

bool isSolvableSet(const Set& set)
{
    unsigned long values = 0;
    for (Set::const_iterator it = set.begin(); it != set.end(); it++)
        values |= *it;
    return set.size() == JEBBase::Bits::countOnes(values);
}

bool findSolvableSubset(Indexes& subset, const Set& set, size_t maxSize)
{

    return false;
}

}
