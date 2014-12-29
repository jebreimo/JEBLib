/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_UNIQUEPAIRSET_HPP
#define JEBBASE_CONTAINERS_UNIQUEPAIRSET_HPP

#include <vector>
#include <utility>
#include "JEBBase/Algorithms/KeyFunctionAlgorithms.hpp"

namespace JEBBase {

template <typename T>
class UniquePairSet
{
public:
    typedef std::pair<T, T> Key;
    typedef std::pair<Key, bool> Value;
    typedef std::vector<Value> Container;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;

    UniquePairSet(const Container& container)
        : m_Container(container)
    {}

    UniquePairSet(Container&& container)
        : m_Container(container)
    {}

    iterator begin() {return m_Container.begin();}
    const_iterator begin() const {return m_Container.begin();}
    iterator end() {return m_Container.end();}
    const_iterator end() const {return m_Container.end();}

    bool get(Key key) const
    {
        if (key.first > key.second)
            std::swap(key.first, key.second);
        auto it = Algorithms::lowerBound(begin(), end(), key,
                [](const Value& v){return v.first;});
        if (it == end() || key != it->first)
        {
            throw std::invalid_argument("Unknown key.");
        }
        return it->second;
    }

    void set(Key key, bool value)
    {
        if (key.first > key.second)
            std::swap(key.first, key.second);
        auto it = Algorithms::lowerBound(begin(), end(), key,
                [](const Value& v){return v.first;});
        if (it == end() || key != it->first)
            throw std::invalid_argument("Unknown key.");
        it->second = value;
    }
private:
    Container m_Container;
};

template <typename T>
class UniquePairSetBuilder
{
public:
    typedef std::pair<T, T> Key;
    typedef std::pair<Key, bool> Value;
    typedef std::vector<Value> Container;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::iterator iterator;

    void add(Key key)
    {
        if (key.first > key.second)
            std::swap(key.first, key.second);
        m_Container.push_back(std::make_pair(key, false));
    }

    Container&& build(bool removeDuplicates = true)
    {
        Algorithms::sortByKey(m_Container.begin(), m_Container.end(),
                              [](const Value& v){return v.first;});
        if (removeDuplicates)
            m_Container.erase(std::unique(
                            m_Container.begin(), m_Container.end(),
                            [](const Value& a, const Value& b)
                              {return a.first == b.first;}),
                    m_Container.end());
        return std::move(m_Container);
    }
private:
    Container m_Container;
};

}

#endif
