#ifndef JEB_JSONLIB_JSONPARSER_HPP
#define JEB_JSONLIB_JSONPARSER_HPP

#include "JsonValue.hpp"

namespace JEB { namespace Json {

class JsonParser
{
public:
    std::unique_ptr<JsonValue> readFile(const std::string& fileName);
    std::unique_ptr<JsonValue> read(std::istream& stream);
    std::unique_ptr<JsonValue> read(const char* str, size_t size);
private:
    size_t m_BufferSize;
};

}}

#endif
