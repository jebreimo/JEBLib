#ifndef JEBSTRING_JEBSTRINGFLAGS_HPP
#define JEBSTRING_JEBSTRINGFLAGS_HPP

#include "JEBStringDefinitions.hpp"

namespace JEBString {

struct Encoding
{
    enum Type
    {
        Unknown,

        Ascii,
        Utf8,
        Latin1,
        Windows1252,
        Utf16,
        Utf16BE,
        Utf16LE = Utf16,
        Utf32,
        Utf32BE,
        Utf32LE = Utf32,
        Utf7,
        Utf1,
        UtfEbcdic,
        Scsu,
        Bocu1,
        Ucs2,
        Gb18030,
        UnspecifiedCodePage, ///< Generic 8-bit encoding

        Maximum
    };
};

typedef Encoding::Type Encoding_t;

struct FindFlags
{
    enum Type
    {
        Defaults = 0,
        CaseInsensitive = 1
    };
    typedef unsigned Flags;

    static bool caseInsensitive(Flags flags)
    {return (flags & CaseInsensitive) != 0;}
};

typedef FindFlags::Flags FindFlags_t;

struct SplitFlags
{
    enum Type
    {
        Defaults = 0,
        CaseInsensitive = 1,
        IgnoreEmpty = 2,
        IgnoreRemainder = 4
    };
    typedef unsigned Flags;

    static bool caseInsensitive(Flags flags)
    {return (flags & CaseInsensitive) != 0;}

    static bool ignoreEmpty(Flags flags)
    {return (flags & IgnoreEmpty) != 0;}

    static bool ignoreRemainder(Flags flags)
    {return (flags & IgnoreRemainder) != 0;}
};

typedef SplitFlags::Flags SplitFlags_t;

struct DecodeResult
{
    enum Type
    {
        Ok = 0,
        EndOfString = 1,
        Incomplete = 2,
        Invalid = 4,
    };
};

typedef DecodeResult::Type DecodeResult_t;

}

#endif
