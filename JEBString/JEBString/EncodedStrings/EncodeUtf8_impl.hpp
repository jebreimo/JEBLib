#include <algorithm>

namespace JEBString { namespace EncodedStrings {

namespace
{
    template <typename OutputIt>
    OutputIt addUtf8_impl(OutputIt it, uint32_t c, size_t length)
    {
        if (length == 1)
        {
            *it++ = (char)c;
        }
        else
        {
            auto shift = (length - 1) * 6;
            *it++ = (char)((0xFF << (8 - length)) | (c >> shift));
            for (size_t i = 1; i < length; i++)
            {
                shift -= 6;
                *it++ = (char)(0x80 | ((c >> shift) & 0x3F));
            }
        }
        return it;
    }
}

template <typename OutputIt>
OutputIt addUtf8(OutputIt it, uint32_t c)
{
    return addUtf8_impl(it, c, utf8EncodedLength(c));
}

template <typename RndIt>
size_t encodeUtf8(RndIt& begin, RndIt end, uint32_t c)
{
    size_t length = utf8EncodedLength(c);
    if (length > (size_t)std::distance(begin, end))
        return 0;
    begin = addUtf8_impl(begin, c, length);
    return length;
}

}}
