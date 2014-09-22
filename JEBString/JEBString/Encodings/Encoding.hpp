#ifndef JEBSTRING_ENCODINGS_ENCODING_HPP
#define JEBSTRING_ENCODINGS_ENCODING_HPP

#include <string>
#include "JEBBase/Bits/Endian.hpp"
#include "JEBString/JEBStringFlags.hpp"
#include "EncodingProperties.hpp"

namespace JEBString { namespace Encodings {

static const size_t ByteOrderMarkMaxLength = 4;

const EncodingProperties* encodingProperties(Encoding_t encoding);

Encoding_t encodingFromName(const std::string& name);
Encoding_t encodingFromByteOrderMark(const std::string& bom);
Encoding_t encodingFromByteOrderMark(const char* bom, size_t len);
Encoding_t encodingFromString(const char* str, size_t len,
                              bool ignoreLastCharacter = false);

/** @brief Returns the most likely encoding used in @a str.
 *
 *  @note There's no guarantee that the encoding returned by this function
 *      actually matches the one used in str, only that str will consist of
 *      legal character values when interpreted as having the returned
 *      encoding.
 *  @note If the length of @a str isn't divisible by 4, UTF-32 encodings will
 *      not be considered, and if it isn't divisble by 2, UTF-16 and other
 *      two-byte encodings will not be considered.
 */
Encoding_t encodingFromString(const std::string& str);

std::pair<Encoding_t, const char*> readEncoding(
        const char* buffer, size_t length);

/** @brief Returns the encoding used in @a stream.
 *
 *  Will look for a byte-order mark (bom) at the start of a stream. If one
 *  is found, return the corresponding encoding and leave the stream at the
 *  first byte after the bom. If one isn't found, read @a maxScanLength
 *  number of bytes, do some basic analysis and try to guess the encoding.
 */
Encoding_t readEncoding(std::istream& stream, size_t maxScanLength = 16);

}}

#endif
