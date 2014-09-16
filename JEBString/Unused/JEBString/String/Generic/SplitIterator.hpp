#ifndef JEB_STRING_SPLITITERATOR_HPP
#define JEB_STRING_SPLITITERATOR_HPP

#include "TokenIterator.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename Iterator, typename Finder>
class SplitIterator
{
private:
    enum State {Normal, LastToken, End};
public:
    SplitIterator(Iterator begin, Iterator end, Finder finder)
        : m_TokenIterator(begin, end, finder),
          m_Start(begin),
          m_Eof(false)
    {}

    SplitIterator(Iterator begin, Iterator end,
                  Iterator tokenBegin, Iterator tokenEnd,
                  Finder finder)
        : m_TokenIterator(begin, end, tokenBegin, tokenEnd, finder),
          m_Start(begin),
          m_Eof(false)
    {}

    bool next()
    {
        m_Start = m_TokenIterator.end();
        if (m_Eof)
            return false;
        if (!m_TokenIterator.next())
            m_Eof = LastToken;
        return true;
    }

    Iterator begin() const {return m_Start;}

    Iterator end() const {return m_TokenIterator.begin();}

    Iterator beginRemainder() const {return m_TokenIterator.end();}

    Iterator endRemainder() const {return m_TokenIterator.endInput();}

    bool empty() const {return begin() == end();}

    bool emptyRemainder() const {return beginRemainder() == endRemainder();}

    /** @brief Returns true if the iterator has reached the end of string.
     */
    bool eof() const {return m_Eof;}
private:
    TokenIterator<Iterator, Finder> m_TokenIterator;
    Iterator m_Start;
    bool m_Eof;
};

template <typename Iterator, typename Finder>
SplitIterator<Iterator, Finder> makeSplitIterator(Iterator begin, Iterator end,
                                                  Finder finder)
{
    return SplitIterator<Iterator, Finder>(begin, end, finder);
}

template <typename Iterator, typename Finder>
class ReverseSplitIterator
{
private:
    enum State {Normal, LastToken, End};
public:
    ReverseSplitIterator(Iterator begin, Iterator end, Finder finder)
        : m_TokenIterator(begin, end, finder),
          m_End(end),
          m_Eof(false)
    {}

    bool next()
    {
        m_End = m_TokenIterator.begin();
        if (m_Eof)
            return false;
        if (!m_TokenIterator.next())
            m_Eof = true;
        return true;
    }

    Iterator begin() const {return m_TokenIterator.end();}

    Iterator end() const {return m_End;}

    Iterator beginRemainder() const {return m_TokenIterator.beginInput();}

    Iterator endRemainder() const {return m_TokenIterator.begin();}

    bool empty() const {return begin() == end();}

    bool emptyRemainder() const {return beginRemainder() == endRemainder();}

    /** @brief Returns true if the iterator has reached the start of string.
     */
    bool eof() const {return m_Eof;}
private:
    ReverseTokenIterator<Iterator, Finder> m_TokenIterator;
    Iterator m_End;
    bool m_Eof;
};

}}}

#endif
