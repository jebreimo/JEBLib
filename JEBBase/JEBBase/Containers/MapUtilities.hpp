/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEB_COLLECTIONS_MAPUTILITIES_HPP
#define JEB_COLLECTIONS_MAPUTILITIES_HPP

#include <map>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T, typename U, typename Cmp>
bool tryGet(const std::map<T, U, Cmp>& map, const T& key, U& value)
{
    typename std::map<T, U, Cmp>::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    value = it->second;
    return true;
}

template <typename T, typename U, typename Cmp>
U get(const std::map<T, U, Cmp>& map, const T& key, const U& defaultValue)
{
    U value;
    if (tryGet(map, key, value))
        return value;
    else
        return defaultValue;
}

template <typename It, typename T>
It findSecond(It begin, It end, const T& value)
{
    while (begin != end && (*begin).second != value)
        begin++;
    return begin;
}

template <typename T, typename U, typename Cmp>
T keyForValue(const std::map<T, U, Cmp>& map, const U& value, const T& defaultKey)
{
    typename std::map<T, U, Cmp>::const_iterator it =
            findSecond(map.begin(), map.end(), value);
    if (it != map.end())
        return it->first;
    else
        return defaultKey;
}

}}

#endif
