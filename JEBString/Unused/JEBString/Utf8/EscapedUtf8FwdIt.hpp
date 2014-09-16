#ifndef JEB_STRING_UTF8_ESCAPEDFWDIT_HPP
#define JEB_STRING_UTF8_ESCAPEDFWDIT_HPP

#include "EscapedUtf8String.hpp"
#include "JEB/Unicode/UnicodeChars.hpp"

namespace JEB { namespace Utf8 {

template <typename FwdIt>
class EscapedUtf8FwdIt
    : std::iterator<std::forward_iterator_tag,
                    std::pair<uint32_t, bool>,
                    ptrdiff_t,
                    const std::pair<uint32_t, bool>*,
                    const std::pair<uint32_t, bool>&>
{
public:
    EscapedUtf8FwdIt();
    EscapedUtf8FwdIt(FwdIt beg, FwdIt end);

    bool operator==(const EscapedUtf8FwdIt& rhs) const;
    bool operator!=(const EscapedUtf8FwdIt& rhs) const;

    EscapedUtf8FwdIt& operator++();
    EscapedUtf8FwdIt operator++(int);

    const std::pair<uint32_t, bool>* operator->() const;
    const std::pair<uint32_t, bool>& operator*() const;

    FwdIt beginSequence() const;
    FwdIt endSequence() const;
private:
    FwdIt m_SeqStart;
    mutable FwdIt m_SeqEnd;
    FwdIt m_End;
    mutable std::pair<uint32_t, bool> m_Value;
};

template <typename FwdIt>
EscapedUtf8FwdIt<FwdIt>::EscapedUtf8FwdIt()
    : m_SeqStart(),
      m_SeqEnd(),
      m_End(),
      m_Value(Unicode::Invalid, false)
{}

template <typename FwdIt>
EscapedUtf8FwdIt<FwdIt>::EscapedUtf8FwdIt(FwdIt beg, FwdIt end)
    : m_SeqStart(beg),
      m_SeqEnd(beg),
      m_End(end),
      m_Value(Unicode::Invalid, false)
{}

template <typename FwdIt>
bool EscapedUtf8FwdIt<FwdIt>::operator==(const EscapedUtf8FwdIt& rhs) const
{
    return m_SeqStart == rhs.m_SeqStart;
}

template <typename FwdIt>
bool EscapedUtf8FwdIt<FwdIt>::operator!=(const EscapedUtf8FwdIt& rhs) const
{
    return !(*this == rhs);
}

template <typename FwdIt>
EscapedUtf8FwdIt<FwdIt>& EscapedUtf8FwdIt<FwdIt>::operator++()
{
    m_SeqStart = endSequence();
    m_Value = std::make_pair(Unicode::Invalid, false);
    return *this;
}

template <typename FwdIt>
EscapedUtf8FwdIt<FwdIt> EscapedUtf8FwdIt<FwdIt>::operator++(int)
{
    EscapedUtf8FwdIt<FwdIt> prev(*this);
    operator++();
    return prev;
}

template <typename FwdIt>
const std::pair<uint32_t, bool>* EscapedUtf8FwdIt<FwdIt>::operator->() const
{
    if (m_Value.first == Unicode::Invalid)
        endSequence();
    return &m_Value;
}

template <typename FwdIt>
const std::pair<uint32_t, bool>& EscapedUtf8FwdIt<FwdIt>::operator*() const
{
    if (m_Value.first == Unicode::Invalid)
        endSequence();
    return m_Value;
}

template <typename FwdIt>
FwdIt EscapedUtf8FwdIt<FwdIt>::beginSequence() const
{
    return m_SeqStart;
}

template <typename FwdIt>
FwdIt EscapedUtf8FwdIt<FwdIt>::endSequence() const
{
    if (m_SeqEnd == m_SeqStart)
        m_Value = unescapeNextUtf8(m_SeqEnd, m_End);
    return m_SeqEnd;
}

}}}

#endif
