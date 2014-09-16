/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_FUNCTIONAL_PAIRS_HPP
#define JEBBASE_FUNCTIONAL_PAIRS_HPP

#include <utility>

namespace JEBBase { namespace Functional {

template <typename T, typename U>
struct Firster
{
    const T& operator()(const std::pair<T, U>& p) const
    {
        return p.first;
    }
};

template <typename T, typename U>
Firster<T, U> firster(const std::vector<std::pair<T, U>>&)
{
    return Firster<T, U>();
}

template <typename T>
std::vector<T> pairToVector(const std::pair<T, T>& p)
{
    std::vector<T> result;
    result.reserve(2);
    result.push_back(p.first);
    result.push_back(p.second);
    return result;
}

template <typename T>
std::vector<T> pairToVector(const std::pair<T, T>&& p)
{
    std::vector<T> result;
    result.reserve(2);
    result.push_back(std::move(p.first));
    result.push_back(std::move(p.second));
    return result;
}

template <typename T, typename U>
struct Seconder
{
    const U& operator()(const std::pair<T, U>& p) const
    {
        return p.second;
    }
};

template <typename T, typename U>
Seconder<T, U> seconder(const std::vector<std::pair<T, U>>&)
{
    return Seconder<T, U>();
}

}}

#endif
