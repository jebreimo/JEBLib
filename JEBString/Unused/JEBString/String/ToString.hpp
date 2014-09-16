#ifndef JEB_STRING_TOSTRING_HPP
#define JEB_STRING_TOSTRING_HPP

#include <sstream>
#include <string>
#include <cstring>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String {

template <typename T>
std::string toString(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

template <typename T>
std::wstring toWString(const T& value)
{
    std::wostringstream stream;
    stream << value;
    return stream.str();
}

template <>
inline std::string toString(const bool& value)
{
    return value ? "true" : "false";
}

template <>
inline std::wstring toWString(const bool& value)
{
    return value ? L"true" : L"false";
}

template <>
inline std::string toString(const std::string& value)
{
    return value;
}

template <>
inline std::wstring toWString(const std::wstring& value)
{
    return value;
}

}}

#endif
