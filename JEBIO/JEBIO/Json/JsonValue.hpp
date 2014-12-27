#ifndef JEB_JSONLIB_JSONVALUE_HPP
#define JEB_JSONLIB_JSONVALUE_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "JsonValueError.hpp"

namespace JEBIO { namespace Json {

class JsonValue;
typedef std::map<std::string, JsonValue> JsonObject;
typedef std::vector<JsonValue> JsonArray;

class JsonValue
{
public:
    enum Type
    {
        Object,
        Array,

        String,
        Real,
        Integer,
        Boolean,
        Null
    };

    JsonValue();
    explicit JsonValue(Type type);
    explicit JsonValue(const JsonObject& object);
    explicit JsonValue(const JsonArray& array);
    explicit JsonValue(const std::string& string);
    explicit JsonValue(const char* string);
    explicit JsonValue(double real);
    explicit JsonValue(int32_t integer);
    explicit JsonValue(int64_t integer);
    explicit JsonValue(uint32_t integer);
    explicit JsonValue(uint64_t integer);
    explicit JsonValue(bool boolean);

    JsonValue(const JsonValue& rhs);
    JsonValue(JsonValue&& rhs);

    ~JsonValue();

    JsonValue& operator=(const JsonValue& rhs);
    JsonValue& operator=(JsonValue&& rhs);

    Type type() const;

    const JsonObject& object() const;
    JsonObject& object();

    const JsonArray& array() const;
    JsonArray& array();

    const std::string& string() const;
    double real() const;
    long long integer() const;
    bool boolean() const;
private:
    union Value
    {
        JsonObject* object;
        JsonArray* array;
        std::string* string;
        double real;
        int64_t integer;
        bool boolean;
    };
    Value m_Value;
    Type m_Type;
};

}}

#endif
