#ifndef JEB_MATH_SUBSET_HPP
#define JEB_MATH_SUBSET_HPP

#include <vector>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEBMath {

typedef std::vector<unsigned long> Set;
typedef std::vector<size_t> Indexes;

bool isSolvableSet(const Set& set);
bool findSolvableSubset(Indexes& subset, const Set& set, size_t maxSize = 0);

}

#endif
