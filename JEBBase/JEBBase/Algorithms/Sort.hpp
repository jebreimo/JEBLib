/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_ALGORITHMS_SORT_HPP
#define JEBBASE_ALGORITHMS_SORT_HPP

#include <utility>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Algorithms {

template <typename T>
void sort(T& a, T& b)
{
    if (b < a)
        std::swap(a, b);
}

template <typename T>
void sort(T& a, T& b, T& c)
{
    sort(a, b);
    sort(b, c);
    sort(a, b);
}

template <typename T>
void sort(T& a, T& b, T& c, T& d)
{
    sort(a, b);
    sort(c, d);
    sort(a, c);
    sort(b, d);
    sort(b, c);
}

template <typename T>
void sort(T (&a)[2])
{
    sort(a[0], a[1]);
}

template <typename T>
void sort(T (&a)[3])
{
    sort(a[0], a[1], a[2]);
}

template <typename T>
void sort(T (&a)[4])
{
    sort(a[0], a[1], a[2], a[3]);
}

}}

#endif
