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

template <typename Node>
class CircularListIterator
{
public:
    CircularListIterator(Node* first);

    bool current() const;
    bool next();
    Node* operator*();
private:
    Node* m_First;
    Node* m_Current;
};

// This is part of a trick to make it possible to use a function named next
// inside CircularListIterator::next.
namespace CircularListIteratorDetail { inline void next() {}}

template <typename Node>
CircularListIterator<Node>::CircularListIterator(Node* first)
    : m_First(first),
      m_Current(NULL)
{
}

template <typename Node>
bool CircularListIterator<Node>::current() const
{
    return m_Current != NULL;
}

template <typename Node>
bool CircularListIterator<Node>::next()
{
    // This using statement tricks the compiler into searching for a function
    // named next in Node's namespace.
    using CircularListIteratorDetail::next;
    if (m_Current)
    {
        m_Current = next(m_Current);
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

template <typename Node>
Node* CircularListIterator<Node>::operator*()
{
    return m_Current;
}

template <typename Node>
CircularListIterator<Node> makeIterator(Node* first)
{
    return CircularListIterator<Node>(first);
}

}}

#endif
