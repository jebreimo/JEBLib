#ifndef JEB_STRING_TOKENITERATOR_HPP
#define JEB_STRING_TOKENITERATOR_HPP

#include <cassert>
#include <utility>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename Iterator, typename Finder>
class TokenIterator
{
public:
    TokenIterator(Iterator begin, Iterator end, Finder finder)
        : m_End(end),
          m_Token(begin, begin),
          m_Finder(finder)
    {}

    TokenIterator(Iterator begin, Iterator end,
                  Iterator tokenBegin, Iterator tokenEnd,
                  Finder finder)
        : m_End(end),
          m_Token(tokenBegin, tokenEnd),
          m_Finder(finder)
    {}

    bool next()
    {
        m_Token = m_Finder(m_Token.second, m_End);
        return m_Token.first != m_Token.second;
    }

    Iterator begin() const {return m_Token.first;}

    Iterator end() const {return m_Token.second;}

    Iterator endInput() const {return m_End;}

    bool eof() const {return m_Token.first == m_End;}
private:
    Iterator m_End;
    std::pair<Iterator, Iterator> m_Token;
    Finder m_Finder;
};

template <typename Iterator, typename Finder>
class ReverseTokenIterator
{
public:
    ReverseTokenIterator(Iterator begin, Iterator end, Finder finder)
        : m_Begin(begin),
          m_Token(end, end),
          m_Finder(finder)
    {}

    bool next()
    {
        m_Token = m_Finder(m_Begin, m_Token.first);
        return m_Token.first != m_Token.second;
    }

    Iterator begin() const {return m_Token.first;}

    Iterator end() const {return m_Token.second;}

    Iterator beginInput() const {return m_Begin;}

    bool eof() const {return m_Begin == m_Token.first;}
private:
    Iterator m_Begin;
    std::pair<Iterator, Iterator> m_Token;
    Finder m_Finder;
};

}}}

#endif