/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_INTERVALMAP_HPP
#define JEBBASE_CONTAINERS_INTERVALMAP_HPP

#include <utility>
#include <vector>
#include "JEBBase/Algorithms/KeyFunctionAlgorithms.hpp"

/** @file
 *  @brief Defines the class IntervalMap<Key, T>.
 */

namespace JEBBase { namespace Containers {

/** @brief A map akin to std::map where the keys are numeric intervals.
 *
 *  Intervals are std::pairs where @a first is @em from, and @a second is @em to,
 *  and they are left-inclusive (or right-exclusive), i.e. find(x) will
 *  consider @a interval a match if interval.first <= x < interval.second.
 */
template <typename Key, typename T>
class IntervalMap
{
public:
    typedef std::pair<Key, Key> Interval;
    typedef std::pair<Interval, T> Value;
    typedef T mapped_type;
    typedef Interval key_type;
    typedef Value value_type;
    typedef typename std::vector<Value>::iterator iterator;
    typedef typename std::vector<Value>::const_iterator const_iterator;

    IntervalMap();

    IntervalMap(Key from, Key to, const T& value);

    /** @brief find the interval that contains @a pos.
     *
     *  @return iterator at the item whose interval contains pos, or
     *      end() of there is no such item.
     */
    iterator find(Key pos);

    /** @brief find the interval that contains @a pos.
     *
     *  @return iterator at the item whose interval contains pos, or
     *      end() of there is no such item.
     */
    const_iterator find(Key pos) const;

    /** @brief insert a new interval along with its associated value.
     */
    void insert(Key from, Key to, const T& value);

    /** @brief insert a new interval along with its associated value.
     */
    void insert(const Interval& interval, const T& value);

    /** @brief return iterator at the first item.
     */
    iterator begin();

    /** @brief return iterator immediately after the last item.
     */
    iterator end();

    /** @brief return iterator at the first item.
     */
    const_iterator begin() const;

    /** @brief return iterator immediately after the last item.
     */
    const_iterator end() const;

    /** @brief returns true if the map has no intervals.
     */
    bool empty() const;

    /** @brief returns the number of intervals in the map.
     */
    size_t size() const;

    void clear();
private:
    std::vector<Value> m_Values;
};

template <typename Key, typename T>
typename IntervalMap<Key, T>::iterator begin(IntervalMap<Key, T>& map)
{
  return map.begin();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::const_iterator begin(const IntervalMap<Key, T>& map)
{
  return map.begin();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::iterator end(IntervalMap<Key, T>& map)
{
  return map.end();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::const_iterator end(const IntervalMap<Key, T>& map)
{
  return map.end();
}

template <typename Key, typename T>
IntervalMap<Key, T>::IntervalMap()
{}

template <typename Key, typename T>
IntervalMap<Key, T>::IntervalMap(Key from, Key to, const T& value)
{
    insert(Interval(from, to), value);
}

template <typename Key, typename T>
void IntervalMap<Key, T>::insert(Key from, Key to, const T& value)
{
    return insert(Interval(from, to), value);
}

namespace detail
{
    template <typename Key, typename T>
    Key getFrom(const typename IntervalMap<Key, T>::Value& value)
    {
        return value.first.first;
    }

    template <typename Key, typename T>
    Key getTo(const typename IntervalMap<Key, T>::Value& value)
    {
        return value.first.second;
    }

    template <typename T>
    bool within(const std::pair<T, T>& interval, T value)
    {
        return interval.first <= value && value < interval.second;
    }
}

template <typename Key, typename T>
void IntervalMap<Key, T>::insert(const Interval& interval, const T& value)
{
    if (interval.first == interval.second)
      return;

    iterator beg = Algorithms::upperBound(
            m_Values.begin(), m_Values.end(),
            interval.first,
            detail::getTo<Key, T>);
    iterator end = Algorithms::lowerBound(
            m_Values.begin(), m_Values.end(),
            interval.second,
            detail::getFrom<Key, T>);

    iterator it;
    if (beg == end)
    {
        m_Values.insert(beg, Value(interval, value));
    }
    else
    {
        Value values[3] = {
            Value(Interval(beg->first.first, interval.first), beg->second),
            Value(Interval(interval.first, interval.second), value),
            Value(Interval(interval.second, (end - 1)->first.second), (end - 1)->second)
        };
        Value* newBeg = &values[0];
        Value* newEnd = &values[3];
        if (newBeg->first.first >= newBeg->first.second)
            newBeg++;
        if ((newEnd - 1)->first.first >= (newEnd - 1)->first.second)
            newEnd--;
        while (newBeg != newEnd && beg != end)
            *beg++ = *newBeg++;
        if (beg != end)
            m_Values.erase(beg, end);
        else
            m_Values.insert(end, newBeg, newEnd);
    }
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::iterator IntervalMap<Key, T>::find(Key pos)
{
    iterator it = Algorithms::upperBound(
            m_Values.begin(), m_Values.end(),
            pos,
            detail::getTo<Key, T>);
    if (it != m_Values.end() && detail::within<Key>(it->first, pos))
        return it;
    else
        return m_Values.end();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::const_iterator IntervalMap<Key, T>::find(Key pos) const
{
    const_iterator it = Algorithms::upperBound(
            m_Values.begin(), m_Values.end(),
            pos,
            detail::getTo<Key, T>);
    if (it != m_Values.end() && detail::within<Key>(it->first, pos))
        return it;
    else
        return m_Values.end();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::iterator IntervalMap<Key, T>::begin()
{
    return m_Values.begin();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::iterator IntervalMap<Key, T>::end()
{
    return m_Values.end();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::const_iterator IntervalMap<Key, T>::begin() const
{
    return m_Values.begin();
}

template <typename Key, typename T>
typename IntervalMap<Key, T>::const_iterator IntervalMap<Key, T>::end() const
{
    return m_Values.end();
}

template <typename Key, typename T>
bool IntervalMap<Key, T>::empty() const
{
  return m_Values.empty();
}

template <typename Key, typename T>
size_t IntervalMap<Key, T>::size() const
{
  return m_Values.size();
}

template <typename Key, typename T>
void IntervalMap<Key, T>::clear()
{
  m_Values.clear();
}

}}

#endif
