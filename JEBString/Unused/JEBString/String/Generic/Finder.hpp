#ifndef JEB_STRING_GENERIC_FINDER_HPP
#define JEB_STRING_GENERIC_FINDER_HPP

#include <cstdint>
#include <iterator>
#include <utility>
#include "JEB/Algorithms/Algorithms.hpp"

namespace JEB { namespace String { namespace Generic {

template <typename FwdIterator, typename BinaryFunc>
class FirstFinder
{
public:
    FirstFinder(FwdIterator begin, FwdIterator end, BinaryFunc comparer)
        : m_Begin(begin),
          m_End(end),
          m_Comparer(comparer)
    {}

    template <typename FwdIterator2>
    std::pair<FwdIterator2, FwdIterator2> operator()(FwdIterator2 begin, FwdIterator2 end) const
    {
        return JEB::Algorithms::search(begin, end, m_Begin, m_End, m_Comparer);
    }
private:
    FwdIterator m_Begin, m_End;
    BinaryFunc m_Comparer;
};

template <typename FwdIt, typename BinaryFunc>
inline FirstFinder<FwdIt, BinaryFunc>
firstFinder(FwdIt begin, FwdIt end, BinaryFunc comparer)
{
    return FirstFinder<FwdIt, BinaryFunc>(begin, end, comparer);
}

template <typename FwdIterator, typename BinaryFunc>
class LastFinder
{
public:
    LastFinder(FwdIterator begin, FwdIterator end, BinaryFunc comparer)
        : m_Begin(begin),
          m_End(end),
          m_Comparer(comparer)
    {}

    template <typename Iterator>
    std::pair<Iterator, Iterator> operator()(Iterator begin, Iterator end) const
    {
        return JEB::Algorithms::search_last(begin, end,
                                            m_Begin, m_End,
                                            m_Comparer);
    }
private:
    FwdIterator m_Begin, m_End;
    BinaryFunc m_Comparer;
};

template <typename FwdIt, typename BinaryFunc>
inline LastFinder<FwdIt, BinaryFunc>
lastFinder(FwdIt begin, FwdIt end, BinaryFunc comparer)
{
    return LastFinder<FwdIt, BinaryFunc>(begin, end, comparer);
}

template <typename FwdIterator, typename BinaryFunc>
class NthLastFinder
{
public:
    NthLastFinder(FwdIterator begin, FwdIterator end,
                  size_t count,
                  BinaryFunc comparer)
        : m_Begin(begin),
          m_End(end),
          m_Count(count),
          m_Comparer(comparer)
    {}

    template <typename Iterator>
    std::pair<Iterator, Iterator> operator()(Iterator begin, Iterator end) const
    {
        return JEB::Algorithms::search_nth_last(begin, end,
                                                m_Begin, m_End,
                                                m_Count,
                                                m_Comparer);
    }
private:
    FwdIterator m_Begin, m_End;
    size_t m_Count;
    BinaryFunc m_Comparer;
};

template <typename FwdIt, typename BinaryFunc>
inline NthLastFinder<FwdIt, BinaryFunc>
nthLastFinder(FwdIt begin, FwdIt end, size_t count, BinaryFunc comparer)
{
    return NthLastFinder<FwdIt, BinaryFunc>(begin, end, count, comparer);
}

template <typename UnaryFunc>
class TokenFinder
{
public:
    TokenFinder(UnaryFunc predicate, bool compress)
        : m_Predicate(predicate),
          m_Compress(compress)
    {}

    template <typename FwdIterator>
    std::pair<FwdIterator, FwdIterator> operator()(FwdIterator begin,
                                                   FwdIterator end) const
    {
        FwdIterator it = std::find_if(begin, end, m_Predicate);
        FwdIterator itStart = (it != end ? it++ : it);
        if (m_Compress)
            it = std::find_if(
                    it, end,
                    [this](uint32_t c){return !m_Predicate(c);});
        return std::make_pair(itStart, it);
    }
private:
    UnaryFunc m_Predicate;
    bool m_Compress;
};

template <typename UnaryFunc>
class LastTokenFinder
{
public:
    LastTokenFinder(UnaryFunc predicate, bool compress)
        : m_Predicate(predicate),
          m_Compress(compress)
    {}

    template <typename FwdIterator>
    std::pair<FwdIterator, FwdIterator> operator()(FwdIterator begin,
                                                   FwdIterator end) const
    {
        FwdIterator itEnd = Algorithms::find_last_if(begin, end, m_Predicate);
        if (itEnd == end)
            return std::make_pair(begin, begin);

        FwdIterator itStart = itEnd++;
        if (m_Compress)
        {
            FwdIterator it = itStart;
            itStart = Algorithms::find_last_if(
                    begin, it,
                    [this](uint32_t c){return !m_Predicate(c);});
            if (itStart != it)
              itStart++;
        }
        return std::make_pair(itStart, itEnd);
    }
private:
    UnaryFunc m_Predicate;
    bool m_Compress;
};

}}}

#endif
