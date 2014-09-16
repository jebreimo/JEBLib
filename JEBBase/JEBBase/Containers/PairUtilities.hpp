/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_UTILITIES_HPP
#define JEBBASE_CONTAINERS_UTILITIES_HPP

#include <utility>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T, typename U>
const T& first(const std::pair<T, U>& pair)
{
    return pair.first;
}

template <typename T, typename U>
const T& second(const std::pair<T, U>& pair)
{
    return pair.second;
}

}}

#endif
