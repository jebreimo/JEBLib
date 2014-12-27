#ifndef JEBSTRING_STREAMS_STREAMFILL_HPP
#define JEBSTRING_STREAMS_STREAMFILL_HPP

#include <ostream>
#include <string>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

template <typename ValueT>
struct OSFiller
{
    OSFiller(size_t n, const ValueT& value)
        : n(n), value(value) {}
    OSFiller(size_t n, ValueT&& value)
        : n(n), value(std::move(value)) {}
    size_t n;
    ValueT value;
};

template <typename StreamT, typename ValueT>
StreamT& operator<<(StreamT& os, OSFiller<ValueT>&& filler)
{
    for (size_t i = 0; i < filler.n; ++i)
        os << filler.value;
    return os;
}

template <typename ValueT>
OSFiller<ValueT> fill(size_t n, ValueT&& str)
{
    return OSFiller<ValueT>(n, str);
}

inline OSFiller<char> spaces(size_t n)
{
    return fill(n, ' ');
}

}

#endif
