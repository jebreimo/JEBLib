//***************************************************************************
// Copyright (C) 2011, Jan Erik Breimo.
// Created 2011-07-18 by Jan Erik Breimo
//***************************************************************************
#ifndef JEBSTRING_UNICODE_CASEINSENSITIVE_HPP
#define JEBSTRING_UNICODE_CASEINSENSITIVE_HPP

#include <cstdint>
#include <functional>
#include <string>
#include "CaseConverter.hpp"

namespace JEBString { namespace Unicode {

inline int32_t caseInsensitiveCompare(uint32_t lhs, uint32_t rhs)
{
    return static_cast<int32_t>(upper(lhs) - upper(rhs));
}

inline bool caseInsensitiveEqual(uint32_t lhs, uint32_t rhs)
{
    return upper(lhs) == upper(rhs);
}

inline bool caseInsensitiveLess(uint32_t lhs, uint32_t rhs)
{
    return upper(lhs) < upper(rhs);
}

struct CaseInsensitiveCompare
    : std::binary_function<uint32_t, uint32_t, int32_t>
{
    int32_t operator()(uint32_t a, uint32_t b) const
    {
        return caseInsensitiveCompare(a, b);
    }
};

struct CaseInsensitiveEqual
    : std::binary_function<uint32_t, uint32_t, bool>
{
    bool operator()(uint32_t a, uint32_t b) const
    {
        return caseInsensitiveEqual(a, b);
    }
};

struct CaseInsensitiveLess
    : std::binary_function<uint32_t, uint32_t, bool>
{
    bool operator()(uint32_t a, uint32_t b) const
    {
        return caseInsensitiveLess(a, b);
    }
};

}}

#endif
