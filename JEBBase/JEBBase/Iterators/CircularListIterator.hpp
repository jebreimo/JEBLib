/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CIRCULARLISTITERATOR_HPP
#define JEBBASE_CIRCULARLISTITERATOR_HPP

#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Iterators {

template <typename Node, typename NextFunc>
class CircularListIterator
{
public:
    /** @param nextNode a function that takes a single argument of Node*
      *     and returns the succeeding Node*.
      */
    CircularListIterator(Node* first, NextFunc nextNode);

    bool current() const;
    bool next();
    Node* operator*();
private:
    NextFunc m_NextNode;
    Node* m_First;
    Node* m_Current;
};

template <typename Node, typename NextFunc>
CircularListIterator<Node, NextFunc>::CircularListIterator(
        Node* first,
        NextFunc nextNode)
    : m_NextNode(nextNode),
      m_First(first),
      m_Current(NULL)
{
}

template <typename Node, typename NextFunc>
bool CircularListIterator<Node, NextFunc>::current() const
{
    return m_Current != NULL;
}

template <typename Node, typename NextFunc>
bool CircularListIterator<Node, NextFunc>::next()
{
    if (m_Current)
    {
        m_Current = m_NextNode(m_Current);
        if (m_Current == m_First)
        {
            m_First = m_Current = NULL;
            return false;
        }
        return true;
    }
    else if (m_First)
    {
        m_Current = m_First;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Node, typename NextFunc>
Node* CircularListIterator<Node, NextFunc>::operator*()
{
    return m_Current;
}

template <typename Node, typename NextFunc>
CircularListIterator<Node, NextFunc> makeIterator(
        Node* first,
        NextFunc nextNode)
{
    return CircularListIterator<Node, NextFunc>(first, nextNode);
}

}}

#endif
