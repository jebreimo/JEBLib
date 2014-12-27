#ifndef JEBSTRING_STREAMS_STREAMJOIN_HPP
#define JEBSTRING_STREAMS_STREAMJOIN_HPP

#include <ostream>
#include <string>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

template <typename FwdIt, typename StringT>
struct OSJoiner
{
    OSJoiner(FwdIt first, FwdIt last, StringT separator)
        : first(first), last(last), separator(separator)
    {}

    FwdIt first, last;
    StringT separator;
};

template <typename StreamT, typename FwdIt, typename StringT>
StreamT& operator<<(StreamT& os, OSJoiner<FwdIt, StringT>&& joiner)
{
    if (joiner.first != joiner.last)
    {
        os << *joiner.first;
        for (auto it = std::next(joiner.first); it != joiner.last; ++it)
            os << joiner.separator << *it;
    }
    return os;
}

template <typename FwdIt, typename StringT>
OSJoiner<FwdIt, StringT> join(FwdIt first, FwdIt last, StringT&& separator)
{
    return OSJoiner<FwdIt, StringT>(first, last, separator);
}

}

#endif
