#ifndef JEB_STRING_FROMSTRING_HPP
#define JEB_STRING_FROMSTRING_HPP

#include <sstream>
#include <string>
#include "JEB/JEBDefinitions.hpp"

namespace JEB { namespace String {

template <typename T>
bool fromString(const std::string& s, T& value)
{
    std::istringstream stream(s);
    stream >> value;
    return !stream.fail();
}

template <typename T>
bool fromString(const std::wstring& s, T& value)
{
    std::wistringstream stream(s);
    stream >> value;
    return !stream.fail();
}

bool fromString(const std::string& s, bool& value);
bool fromString(const std::wstring& s, bool& value);
bool fromString(const std::string& s, std::string& value);
bool fromString(const std::wstring& s, std::wstring& value);
bool fromString(std::string&& s, std::string& value);
bool fromString(std::wstring&& s, std::wstring& value);
bool fromString(const std::string& s, double value);
bool fromString(const std::wstring& s, double value);
bool fromString(const std::string& s, long& value, int base = 10);
bool fromString(const std::wstring& s, long& value, int base = 10);

}}

#endif
