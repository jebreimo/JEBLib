/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_SETUTILITIES_HPP
#define JEBBASE_CONTAINERS_SETUTILITIES_HPP

#include <iterator>
#include <set>
#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T, typename Less>
bool has(const std::set<T, Less>& set, const T& value)
{
    return set.find(value) != set.end();
}

template<class Container>
class set_inserter_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    set_inserter_iterator(Container& cont)
        : container(cont)
    {
    }

    set_inserter_iterator& operator=(const typename Container::value_type& value)
    {
        container.insert(value);
        return *this;
    }

    set_inserter_iterator& operator*()
    {
        return *this;
    }

    set_inserter_iterator& operator++()
    {
        return *this;
    }

    set_inserter_iterator& operator++(int)
    {
        return *this;
    }

private:
    Container& container;
};

template<typename Container>
inline set_inserter_iterator<Container> set_inserter(Container& cont)
{
    return set_inserter_iterator<Container>(cont);
}

}}

#endif
